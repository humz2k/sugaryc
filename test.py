#------------------------------------------------------------------------------
# pycparser: c-to-c.py
#
# Example of using pycparser.c_generator, serving as a simplistic translator
# from C to AST and back to C.
#
# Eli Bendersky [https://eli.thegreenplace.net/]
# License: BSD
#------------------------------------------------------------------------------
import sys

# This is not required if you've installed pycparser into
# your site-packages/ with setup.py
sys.path.extend(['.', '..'])

from pycparser import c_parser, c_generator, c_ast

def type2string(typ):
    if (type(typ) == c_ast.TypeDecl):
        return type2string(typ.type)
    if (type(typ) == c_ast.PtrDecl):
        return type2string(typ.type) + "_ptr"
    if (type(typ) == c_ast.Struct):
        return "struct_" + typ.name
    if (type(typ) == c_ast.IdentifierType):
        return "_".join(typ.names)
    print(typ)
    print("NOT IMPLEMENTED",type(typ))
    exit()

class FunctionMangler(c_ast.NodeVisitor):
    def visit_FuncDecl(self,node : c_ast.FuncDecl):
        base_name = node.type.declname
        if (base_name == "main"):
            return
        param_list = node.args.params
        for i in param_list:
            base_name += "__" + type2string(resolve_type_def(i.type))
        node.type.declname = base_name


typedefs = {}

def resolve_type_def(node):
    global typedefs
    if (type(node) == c_ast.IdentifierType):
        try:
            return typedefs[node.names[-1]]
        except:
            return node
    try:
        node.type = resolve_type_def(node.type)
    except:
        pass
    return node

class TypeDefCacher(c_ast.NodeVisitor):
    def visit_Typedef(self, node):
        global typedefs
        typedefs[node.name] = resolve_type_def(node.type)


text = """


struct test{
    int a;
};

typedef struct test* TEST;

void my_func(int a){
    return;
}

void my_func(float a){
    return;
}

int main(){

    TEST yeet;
    struct test a;
    int b = a.a(5);

    return 0;
}


"""

parser = c_parser.CParser()
ast = parser.parse(text)

#ast.show(offset=2)

v = TypeDefCacher()
v.visit(ast)

v = FunctionMangler()
v.visit(ast)

generator = c_generator.CGenerator()
print(generator.visit(ast))