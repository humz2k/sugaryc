from pycparser import c_parser, c_generator, c_ast

functions = {}

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
        global functions
        base_name = node.type.declname
        if (base_name == "main"):
            return
        param_list = node.args.params
        for i in param_list:
            base_name += "__" + type2string(i.type)
        node.type.declname = base_name
        functions[base_name] = node