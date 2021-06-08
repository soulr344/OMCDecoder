#include <sstream>
#include <fstream>
#include <iostream>
#include <string.h>
#include <gzip/decompress.hpp>
#include <gzip/compress.hpp>
#include "include.h"

void usage(char *argv0){
    fprintf(stderr, R"EOF(OMC Text Decoder

Usage: %s [options] infile outfile

Options:
    -d/--decode     Decodes infile and saves to outfile (default)
    -e/--encode     Encodes infile and saves to outfile
    -i/--in-place   Save output to infile (outfile is ignored)

)EOF", argv0);
    exit(-1);
}

int main(int argc, char**argv){
    char *argv0 = argv[0];
    bool encode = false, inplace = false;
    std::string infile, outfile;

    if (argc < 3){
        usage(argv0);
    }

    for (int i=1; i<argc; i++){
        char *arg = argv[i];
        if (strcmp(arg, "-e") == 0 || strcmp(arg, "--encode") == 0){
            encode = true;
        } else if (strcmp(arg, "-d") == 0 || strcmp(arg, "--decode") == 0){
            encode = false;
        } else if (strcmp(arg, "-i") == 0 || strcmp(arg, "--in-place") == 0){
            inplace = true;
        } else {
            if (infile.compare("") == 0){
                infile = arg;
            } else if (outfile.compare("") == 0) {
                outfile = arg;
            } else {
                fprintf(stderr, "Unrecognized argument(s) %s\n", arg);
                exit(-1);
            }
        }
    }
    if (inplace){
        outfile = infile;
    }
    if (outfile.compare("") == 0) {
        fprintf(stderr, "Fatal: no output file specified! Either use -i or specify an output file.\n");
        exit(-1);
    }

    std::ifstream inFile;
    inFile.open(infile);
    if (!inFile.good()){
        fprintf(stderr, "Fatal: Can't find infile %s!\n", infile.c_str());
        inFile.close();
        exit(-1);
    }
    std::string data((std::istreambuf_iterator<char>(inFile)),
                 std::istreambuf_iterator<char>());

    inFile.close();

    OMCTextDecoder decoder;
    std::ofstream out(outfile);
    if (!encode){
        out << decoder.gzipDecompress(decoder.decode(data));
    } else {
        out << decoder.encode(decoder.gzipCompress(data));
    }

    out.close();
    return 0;
}