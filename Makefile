LIB_NAME		= ALF_std
STC_LIB_PRE		= lib
STC_LIB_EXT		= a
DYN_LIB_PRE		= lib
DYN_LIB_EXT		= so
ifeq ($(OS),Windows_NT)
	STC_LIB_PRE		= 
	STC_LIB_EXT		= lib
	DYN_LIB_PRE		= 
	DYN_LIB_EXT		= dll
endif

LIB_STATIC		= $(STC_LIB_PRE)$(LIB_NAME).$(STC_LIB_EXT)
LIB_DYNAMIC		= $(DYN_LIB_PRE)$(LIB_NAME).$(DYN_LIB_EXT)


# Directories
PATH_SEPARATOR	= /
ifeq ($(OS),Windows_NT)
	PATH_SEPARATOR	= \\
endif
SRC_DIR		= src
OBJ_DIR		= obj
INCLUDE_DIR	= include/ src/
OUT_DIR		= out
DOCS		= docs
TESTS		= tests
LIBS_DIR	= lib/ src/
OUT_LIB_DIR	= $(OUT_DIR)$(PATH_SEPARATOR)lib
OUT_INC_DIR	= $(OUT_DIR)$(PATH_SEPARATOR)include

FOLDERS		= $(OBJ_DIR) $(OUT_DIR) $(OUT_LIB_DIR) $(OUT_INC_DIR)
RM_FOLDERS	= $(OBJ_DIR) $(OUT_DIR)

# Compiler
CC			= @gcc
LANG_EXT	= c
HEADER_EXT	= h
OBJ_EXT		= o
FLAGS		= -Wall -fPIC
SHARED_FLAG	= -shared
DEBUG_FLAG	= -g
LIBS		= 
LIBS_NAMES	= $(addprefix -l, $(LIBS))
LIBS_FOLDER	= $(addprefix -L, $(LIBS_DIR))
INCLUDE_FOLD= $(addprefix -I, $(INCLUDE_DIR))

# 
AR			= @ar
AR_FLAGS	= cvq

# Doxygen, documentation generator
DOXYGEN		= doxygen 

# Commands
ECHO		= @echo
COPY		= @cp
COPY_FLAGS	= -R
MOVE		= @mv
MAKEDIR		= @mkdir
MKDIR_FLAGS	= -p
REMOVE		= @rm
RM_FLAGS	= -rf
INSTALL_COM	= @install

ifeq ($(OS),Windows_NT)
	COPY_FLAGS	= 
	MKDIR_FLAGS	= 
	REMOVE		= @rd
	RM_FLAGS	= /s /q
	MOVE		= move
endif

TEST_SRC	= $(wildcard $(TESTS)/*.$(LANG_EXT))
TEST_EXE	= $(patsubst $(TESTS)/%.$(LANG_EXT), $(TESTS)/%, $(TEST_SRC))

SRC_FILES	= $(wildcard $(SRC_DIR)/*.$(LANG_EXT))
OBJ_O		= $(patsubst $(SRC_DIR)/%.$(LANG_EXT), $(OBJ_DIR)/%.$(OBJ_EXT), $(SRC_FILES))

all: dynamic_lib # static_lib
	$(COPY) $(COPY_FLAGS) $(SRC_DIR)$(PATH_SEPARATOR)$(LIB_NAME).$(HEADER_EXT) $(OUT_INC_DIR)$(PATH_SEPARATOR)
	$(COPY) $(COPY_FLAGS) $(SRC_DIR)$(PATH_SEPARATOR)$(LIB_NAME)$(PATH_SEPARATOR) $(OUT_INC_DIR)$(PATH_SEPARATOR)
	$(ECHO) "Done\n"
	$(ECHO) $(PREFIX)

debug: make_debug_objects ar_static_lib compile_dynamic_lib
	$(ECHO) "Debug ready\n"

install: dynamic_lib #static_lib
	$(INSTALL_COM) $(OUT_LIB_DIR)/* --target-directory=/usr/lib/
	$(INSTALL_COM) -d /usr/include/$(LIB_NAME)
	$(INSTALL_COM) $(OUT_INC_DIR)/$(LIB_NAME).$(HEADER_EXT) /usr/include/
	$(INSTALL_COM) $(OUT_INC_DIR)/$(LIB_NAME)/* --target-directory=/usr/include/$(LIB_NAME)/

clean:
	$(REMOVE) $(RM_FLAGS) $(RM_FOLDERS)
	$(REMOVE) $(TEST_EXE)

docs: make_docs_folder doxygen_make_docs
	$(ECHO) "done"

tests: $(TEST_EXE)
	$(ECHO) "Tests done."


$(TESTS)/%: $(TESTS)/%.$(LANG_EXT)
	$(ECHO) $(CC) $<
	$(CC) $< -o $@ $(FLAGS) $(INCLUDE_FOLD) $(LIBS_FOLDER) $(LIBS_NAMES) -L$(OUT_LIB_DIR) -l$(LIB_NAME)


make_docs_folder:
	$(MAKEDIR) $(MKDIR_FLAGS) $(DOCS)
doxygen_make_docs: make_docs_folder
	$(DOXYGEN) docs.conf

clean_docs:
	$(REMOVE) $(RM_FLAGS) $(DOCS)


static_lib: make_objects ar_static_lib
	$(ECHO) "\tStatic library done\n"

dynamic_lib: make_objects compile_dynamic_lib
	$(ECHO) "\tDynamic library done\n"


makefolders:
	$(ECHO) "Making folders"
	$(MAKEDIR) $(MKDIR_FLAGS) $(FOLDERS)
	$(ECHO) "\tFolders done\n"

$(OBJ_DIR)/%.$(OBJ_EXT): $(SRC_DIR)/%.$(LANG_EXT)
	$(ECHO) $(CC) -c $< 
	$(CC) -c $< -o $@ $(FLAGS) $(INCLUDE_FOLD) $(LIBS_FOLDER) $(LIBS_NAMES)

make_objects: makefolders $(OBJ_O)
	$(ECHO) "\tObjects done\n"

make_debug_objects: makefolders
	$(ECHO) "Making objects"
	$(CC) -c $(SRC_DIR)$(PATH_SEPARATOR)*.$(LANG_EXT) $(FLAGS) $(DEBUG_FLAG) $(INCLUDE_FOLD) $(LIBS_FOLDER) $(LIBS_NAMES)
	$(ECHO) "->Moving files"
	$(MOVE) *.$(OBJ_EXT) $(OBJ_DIR)$(PATH_SEPARATOR)
	$(ECHO) "\tObjects done\n"

ar_static_lib: make_objects
	$(ECHO) "Making static lib"
	$(ECHO) $(AR) $(OUT_LIB_DIR)$(PATH_SEPARATOR)$(LIB_STATIC)
	$(AR) $(AR_FLAGS) $(OUT_LIB_DIR)/$(LIB_STATIC) $(OBJ_DIR)/*.$(OBJ_EXT)
	$(ECHO) "->Static lib done"

compile_dynamic_lib: make_objects
	$(ECHO) "Making dynamic lib"
	$(ECHO) $(CC) $(OUT_LIB_DIR)$(PATH_SEPARATOR)$(LIB_DYNAMIC) $(SHARED_FLAG)
	$(CC) $(OBJ_DIR)/*.$(OBJ_EXT) $(SHARED_FLAG) -o $(OUT_LIB_DIR)/$(LIB_DYNAMIC) $(INCLUDE_FOLD) $(LIBS_FOLDER) $(LIBS_NAMES)
	$(ECHO) "->Dynamic lib done"
