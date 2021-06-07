# OMCDecoder
Samsung OMC Decoder implementation in C++ from CSC apk.

# Usage
```
cscdecoder [options] input.xml output.xml

Options:
    -d/--decode     Decodes input.xml and saves to output.xml (default)
    -e/--encode     Encodes input.xml and saves to output.xml
    -i/--in-place   Save output to input.xml (output.xml is ignored)
```

# How to Compile
```clang++ -lz -I./include decoder.cpp -o cscdecoder```

# Credits

### [@mapbox](https://github.com/mapbox/gzip-hpp)
