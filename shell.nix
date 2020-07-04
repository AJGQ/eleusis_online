with import <nixpkgs> {}; {
    eleusisEnv = gcc8Stdenv.mkDerivation {
        name = "eleusis-env";
        buildInputs = [ gcc
                        gdb
                        pkgconfig
                      ];
    };
}
