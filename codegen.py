from pycparser import c_parser, c_generator, c_ast
from mangler import *
from typedef_cacher import *
from llvmlite import ir

text = """

int test(void){
    const int a = 1;
    return 0;
}

"""

class C2LLVM(c_ast.NodeVisitor):
    def visit_IdentifierType(self, node : c_ast.IdentifierType):
        if (tuple(node.names) == ('int',)):
            return ir.IntType(32)
        if (tuple(node.names) == ('short', 'int',) or (tuple(node.names) == ('short'))):
            return ir.IntType(16)
        if (type(node.names) == ('void')):
            return ir.VoidType()
        
    def visit_TypeDecl()
        
    def visit_FuncDecl(self, node : c_ast.FuncDecl):
        print(node)


parser = c_parser.CParser()
ast = parser.parse(text)

v = TypeDefCacher()
v.visit(ast)

v = C2LLVM()
v.visit(ast)

#ast.show(offset = 2)

#generator = c_generator.CGenerator()
#print(generator.visit(ast))