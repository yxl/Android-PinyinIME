CPP=g++
CPPFLAGS= -g3 -Wall -m32

TARGET=test_pinyin

LIBRARY_SRC= \
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
        ConvertUTF.cpp \
        test.cpp

all: $(TARGET) test

test: $(TARGET)
	$(TARGET)

$(TARGET): $(LIBRARY_SRC)
	@$(CPP) $(CPPFLAGS) -o $@ $?


clean:
	-rm -rf $(TARGET) user.dic

.PHONY: clean
