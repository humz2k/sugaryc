import sys
import os
sys.path = [os.path.abspath(os.path.join(os.path.dirname( __file__ ), '..'))] + sys.path
from pycparser import c_generator, parse_file, c_ast, ParseError
import argparse
import re

class KernelFixer(c_ast.NodeVisitor):
    def visit_Decl(self, node : c_ast.Decl):
        if (not "__global__" in node.quals):
            return
        if not isinstance(node.type,c_ast.FuncDecl):
            return
        
        typ = node.type

        if not typ.args:
            typ.args = c_ast.ParamList(params = [])

        new_inps = []
        for v in ["blockIdx","blockDim","threadIdx"]:
            ty = c_ast.TypeDecl(declname=v, quals=[], align=[], type=c_ast.IdentifierType(['int3']))
            newdecl = c_ast.Decl(name=v,quals=[],align=[],storage=[],funcspec=[],type=ty,init=None,bitsize=None,coord=node.coord)
            new_inps.append(newdecl)
        typ.args.params = new_inps + typ.args.params

        node.type = typ