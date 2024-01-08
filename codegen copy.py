from pycparser import c_parser, c_generator, c_ast
from llvmlite import ir

class GlobalState:
    def __init__(self):
        self.struct_decls = {}
        self.typedefs = {}

    def add_struct_decl(self,name,decls):
        assert(name not in self.struct_decls)
        self.struct_decls[name] = decls
    
    def get_struct_decl(self,name):
        assert(name in self.struct_decls)
        return self.struct_decls[name]
        
    def add_typedef(self,name,typ):
        assert(not name in self.typedefs)
        self.typedefs[name] = typ

    def get_typedef(self,name):
        assert(name in self.typedefs)
        return self.typedefs[name]

state = GlobalState()

class FindStructDecls(c_ast.NodeVisitor):
    def visit_Struct(self, node : c_ast.Struct):
        global state
        if (not node.decls is None):
            state.add_struct_decl(node.name, node.decls)
        self.generic_visit(node)

class ResolveStructDecls(c_ast.NodeVisitor):
    def visit_Struct(self, node : c_ast.Struct):
        global state
        if node.decls is None:
            try:
                node.decls = state.get_struct_decl(node.name)
            except:
                pass
        self.generic_visit(node)

class ResolveTypeDefs(c_ast.NodeVisitor):
    def visit_Typedef(self, node : c_ast.Typedef):
        global state

    def visit_Decl(self, node : c_ast.Decl):
        global state
        if type(node.type) == c_ast.IdentifierType:
            print(node)

class PrintStructDecls(c_ast.NodeVisitor):
    def visit_Struct(self, node : c_ast.Struct):
        global state
        #print(node)
    

text = """

struct test;

typedef struct test TEST;

TEST yes;

"""


parser = c_parser.CParser()
ast = parser.parse(text)

FindStructDecls().visit(ast)
ResolveStructDecls().visit(ast)
ResolveTypeDefs().visit(ast)
#PrintStructDecls().visit(ast)

#ast.show(offset=2)