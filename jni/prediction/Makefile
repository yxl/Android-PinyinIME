CPP=g++
CPPFLAGS= -g3 -m32 -Wall

TARGET=prediction

LIBRARY_SRC= \
        main.cpp \
        ConvertUTF.cpp \
        ../share/dictbuilder.cpp \
        ../share/dictlist.cpp \
        ../share/dicttrie.cpp \
        ../share/lpicache.cpp \
        ../share/mystdlib.cpp \
        ../share/ngram.cpp \
        ../share/searchutility.cpp \
        ../share/spellingtable.cpp \
        ../share/spellingtrie.cpp \
        ../share/splparser.cpp \
        ../share/utf16char.cpp \
        ../share/utf16reader.cpp \
        ../share/matrixsearch.cpp \
        ../share/pinyinime.cpp \
        ../share/userdict.cpp \

all: $(TARGET) $(TARGET).js lib$(TARGET).html native_test js_test

$(TARGET): $(LIBRARY_SRC)
	@$(CPP) $(CPPFLAGS) -o $@ $?

lib$(TARGET).html: $(TARGET).bc dict_pinyin.png
	emcc -O3 --closure 1 -o $@ $(TARGET).bc -s ASM_JS=1 -s EXPORTED_FUNCTIONS="['_InitPrediction', '_ExitPrediction', '_GetPrediction']" --preload-file dict_pinyin.png

$(TARGET).js: $(TARGET).bc dict_pinyin.png
	emcc -O3 -o $@ $(TARGET).bc -s ASM_JS=1 -s EXPORTED_FUNCTIONS="['_main', '_InitPrediction', '_ExitPrediction', '_GetPrediction']" --embed-file dict_pinyin.png

$(TARGET).bc: $(LIBRARY_SRC)
	emcc -O3 -o $@ $(LIBRARY_SRC) 

dict_pinyin.png:
	cp ../../res/raw/dict_pinyin.png .

native_test: $(TARGET) dict_pinyin.png
	./$(TARGET)

js_test: $(TARGET).js
	node $(TARGET).js

clean:
	rm -rf *.html $(TARGET) *.js *.bc *.data
	rm -rf dict_pinyin.png dummy_user_dict
	rm -rf *.map *.o

.PHONY: clean test
