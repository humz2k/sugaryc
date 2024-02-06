import json
import sys
import os
sys.path = [os.path.abspath(os.path.join(os.path.dirname( __file__ ), '..'))] + sys.path
from pycparser import c_generator, parse_file, c_ast, ParseError
from pysgcc import *
import argparse
import re

def replace_T(code, replacement, T):
    # Regex pattern to match string literals or \bT\b
    pattern = r'\"(?:\\.|[^"\\])*\"|\'(?:\\.|[^\'\\])*\'|\b' + T + r'\b'

    def replacer(match):
        # If the match is T, replace it; otherwise, return the match unchanged
        return replacement if match.group(0) == T else match.group(0)

    return re.sub(pattern, replacer, code)

class GeneratedTemplate:
    def __init__(self, gen_strs, code, Ts):
        """
        Initializes the GeneratedTemplate instance.
        :param gen_strs: List of strings representing generator identifiers.
        :param code: The code template that needs to be processed.
        :param Ts: List of placeholder strings in the code that are to be replaced.
        """
        self.code = code          # The template code
        self.Ts = Ts              # Placeholders in the template code
        self.gen_strs = gen_strs  # Identifiers for the generator
        self.generated = []       # Keeps track of combinations that have already been generated

    def get_replacer(self):
        """
        Creates a unique replacer string based on generator identifiers and placeholders.
        This replacer string is used to identify where in the code the template should be injected.
        :return: A string that acts as a placeholder for where the generated code should be injected.
        """
        return "__generate(" + "_".join(self.gen_strs) + "__" + "_".join(self.Ts) + ")\n"

    def generate(self, code, reTs):
        """
        Generates code by replacing placeholders in the template with actual values.
        If the code with the same replacements has already been generated, it returns the original code.
        :param code: The original code where the generated code needs to be injected.
        :param reTs: The actual values that will replace the placeholders in the template.
        :return: The code with the template replaced by the actual values.
        """
        # Create a unique identifier for the current combination of replacements
        current_gen = tuple(i.strip().replace(" ", "") for i in reTs)

        # If this combination was already generated, return the original code
        if current_gen in self.generated:
            return code

        # Record that this combination has now been generated
        self.generated.append(current_gen)

        # Ensure the number of replacements matches the number of placeholders
        assert len(reTs) == len(self.Ts), "Mismatch between placeholders and replacements"

        # Replace placeholders in the template with actual values
        out_str = self.code
        for t, T in zip(reTs, self.Ts):
            out_str = replace_T(out_str, t, T)

        # Insert the generated code into the original code and return
        return code.replace(self.get_replacer(), out_str + "\n" + self.get_replacer())

def extract_first_block(content):
    """
    Extracts and returns the first block of code (enclosed by {}) from the given content.
    This is particularly useful for extracting the body of a function or a template from source code.

    :param content: The string from which the first block of code is to be extracted.
    :return: The first block of code (enclosed by {}) found in the content.
    """

    block_code = ""  # Initialize the string to hold the code block
    depth = 0  # Depth of nested braces

    # Iterate through each character in the content
    for char in content:
        # Increment depth for each opening brace
        if char == "{":
            depth += 1

        # Decrement depth for each closing brace
        if char == "}":
            depth -= 1
            # If depth goes negative, we've found the end of the first code block
            if depth < 0:
                break

        # Append the current character to the block_code if we are inside a code block
        block_code += char

    # Return the captured code block
    return block_code

def handle_templates(raw):
    """
    Recursively processes and replaces template functions in the input string.

    It looks for patterns that match template syntax, extracts the template arguments,
    and replaces the template parameters with actual types. This is done for each template
    function found in the input string.

    :param raw: The string containing the code with templates.
    :return: The processed string with all template instances expanded.
    """

    # Regex to find template function definitions
    template_pattern = r'\btemplate\s*<\b.+\=(.*)>.?\{'
    match = re.search(template_pattern, raw)

    # If no template is found, return the raw input
    if match is None:
        return raw

    # Extract the full template function string
    template_str = match.string[match.span()[0]:match.span()[1]]

    # Extract the function code after the template definition
    function_code = raw[match.span()[1]:]

    # Extract the first block of code (template function body)
    function_body = extract_first_block(function_code)

    # Extract template argument types
    template_args = "".join("".join(template_str.split("<")[1:]).split(">")[:-1])
    placeholder = template_args.split("=")[0].strip()
    actual_types = [type_str.strip() for type_str in template_args.split("=")[1].split(",")]

    # Initialize the output string
    processed_code = ""

    # Replace the placeholder in the template with each actual type
    for actual_type in actual_types:
        processed_code += replace_T(function_body, actual_type, placeholder) + "\n"

    # Construct the string to be replaced in the raw input
    to_replace = template_str + function_body + "}"

    # Replace the template definition and body in the raw input
    processed_raw = raw.replace(to_replace, processed_code)

    # Recursively process the next template
    return handle_templates(processed_raw)

generateds = {}

def reset_generated():
    global generateds
    generateds = {}

def handle_generated(raw_code):
    """
    Recursively processes 'generated' blocks in the input string (source code).

    For each 'generated' block found, it extracts generator strings and placeholders,
    replaces the placeholders in the block with actual generator strings, and keeps track
    of the processed blocks to avoid processing the same block multiple times.

    :param raw_code: The string containing the code with 'generated' blocks.
    :return: The processed string with all 'generated' blocks expanded.
    """

    global generateds

    # Regex pattern to find 'generated' blocks
    generated_pattern = r'\bgenerated\b(.+)<(.*)>.?\{'
    match = re.search(generated_pattern, raw_code)

    # If no 'generated' block is found, return the raw input
    if match is None:
        return raw_code

    # Extract generator strings and placeholders
    gen_strs = [item.strip() for item in match.group(1).split(",")]
    placeholders = [item.strip() for item in match.group(2).split(",")]

    # Extract the block of code after the 'generated' definition
    block_code = raw_code[match.span()[1]:]

    # Extract the first block of code (generated block body)
    generated_body = extract_first_block(block_code)

    # Construct the full 'generated' block string to be replaced
    generated_block_str = match.string[match.span()[0]:match.span()[1]]
    to_replace = generated_block_str + generated_body + "}"

    # Create a GeneratedTemplate object for the current 'generated' block
    generated_template = GeneratedTemplate(gen_strs, generated_body, placeholders)

    # Update the global 'generateds' dictionary with the current 'generated' block
    for gen_str in gen_strs:
        generateds[gen_str] = generated_template

    # Replace the 'generated' block definition and body in the raw input
    processed_raw_code = raw_code.replace(to_replace, generated_template.get_replacer())

    # Recursively process the next 'generated' block
    return handle_generated(processed_raw_code)

def replace_innermost_brackets(code):
    # Pattern to match the innermost angle brackets
    pattern = r'(\w+)<([^<>]+)>'

    if re.search(pattern,code) is None:
        return code

    to_gen = []
    # Function to replace angle brackets with parentheses
    def replacer(match):
        # Extract the string before the angle brackets
        string_before_brackets = match.group(1)
        gen_str = string_before_brackets.strip()
        if (gen_str in generateds):
            Ts = [i.strip() for i in match.group(2).split(",")]
            to_gen.append((generateds[gen_str],Ts))
        replaces = {
            "*": "ptr",
            "%": "mod",
            "=": "eq",
            "+": "add",
            "-": "sub",
            "/": "div",
            "<": "lt",
            ">": "gt",
            "(": "lpar",
            ")": "rpar",
            "!": "not",
            "~": "neg",
            ":": "colon",
            "?": "question"
        }

        tmp = [i.strip().replace(" ","") for i in match.group(2).split(",")]
        out = []
        for i in tmp:
            t = i
            for j in replaces:
                t = t.replace(j,replaces[j])
            out.append(t)
        tmp = out
        # Replace angle brackets with parentheses and prepend the processed string
        return string_before_brackets + '__template__' + "__".join(tmp)

    # Apply the regex replacement repeatedly until there are no more matches
    while re.search(pattern, code):
        code = re.sub(pattern, replacer, code)
    for i,j in to_gen:
        code = i.generate(code,j)
    return replace_innermost_brackets(code)

def handle_struct_templates(raw):
    return replace_innermost_brackets(raw)


def handle_modules(raw):
    out = re.search(r'\bmodule\s+(\w*);', raw)
    if out is None:
        return raw
    raw = re.sub(out.group(0),'',raw)
    out = out.group(1)
    pattern = r'\b' + out + r'\s*\.\s*'
    raw = re.sub(pattern,out + "__",raw)
    return handle_modules(raw)

n_foreach = 0

def replace_foreach(code):
    pattern = r"\bforeach\s*\((.*)\)"

    if re.search(pattern,code) is None:
        return code

    to_gen = []
    def replacer(match):
        global n_foreach
        n_foreach += 1
        l,r = match.group(1).split(" in ")
        var_name = l.split(" ")[-1]
        itername = "__iter_foreach_" + str(n_foreach)
        out = "auto " + itername + " = __iter__(" + r + "); for(" + l + " = __start__(" + itername + "); !__done__(" + itername + "); " + var_name + " = __next__(" + itername + "))"
        return out

    # Apply the regex replacement repeatedly until there are no more matches
    while re.search(pattern, code):
        code = re.sub(pattern, replacer, code)
    return replace_foreach(code)

def handle_foreach(raw):
    return replace_foreach(raw)