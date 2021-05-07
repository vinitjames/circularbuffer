from conans import ConanFile, CMake


class CircularBufferConan(ConanFile):
    name = "circular_buffer"
    version = "0.1.0"
    license = "MIT License"
    author = "vinit james  vinit.james24@gmail.com"
    url = "https://github.com/vinitjames/circularbuffer"
    description = "A simple, general purpose STL style circularbuffer implementation in C++."
    topics = ("circularbuffer", "ringbuffer", "conan-recipe", "c++")
    exports_sources = "*"

    def build(self): # this is not building a library, just tests
        cmake = CMake(self)
        cmake.configure()
        cmake.build()
        cmake.test()
    
    def package(self):
        print(self.name)
        self.copy("{}.h".format(self.name), dst="include", src=".")
        self.copy("LICENSE", dst="license", src=".")

    def package_info(self):
        self.info.header_only()
