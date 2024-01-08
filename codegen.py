from pycparser import c_parser, c_generator, parse_file
import sys
import os

if __name__ == "__main__":
    if len(sys.argv) > 1:
        #with open(sys.argv[1],"r") as f:
        #    text = f.read()
        pass
    else:
        print("Please provide a filename as argument")
        exit(1)

    #parser = c_parser.CParser()
    #ast = parser.parse(text)
    ast = parse_file(sys.argv[1], use_cpp=True,
        cpp_path='cpp',
        cpp_args=r'-Istdlib')

    generator = c_generator.CGenerator()

    temp_file = "__temp__.cpp"

    out = generator.visit(ast)

    #out = out.replace("__add__","operator +")
    with open("ops.hpp","r") as ops:
        out = ops.read() + out

    with open(temp_file,"w") as f:
        f.write(out)
    os.system("g++ " + temp_file + " -o temp.o")
    