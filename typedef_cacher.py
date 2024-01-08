from pycparser import c_parser, c_generator, c_ast

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

    def visit_TypeDecl(self, node):
        node.type = resolve_type_def(node.type)