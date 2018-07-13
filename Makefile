LIB_NAME		= ALF_std
STC_LIB_PRE		= lib
STC_LIB_EXT		= a
DYN_LIB_PRE		= lib
DYN_LIB_EXT		= so


# Directories
SRC_DIR		= src
OBJ_DIR		= obj
INCLUDE_DIR	= include
EXTRA_DIR	= extra
OUT_DIR		= out

O_EXT_DIR	= $(OBJ_DIR)/$(EXTRA_DIR)
STATIC_DIR	= $(OUT_DIR)/static
DYNAMIC_DIR	= $(OUT_DIR)/dynamic

FOLDERS		= $(OBJ_DIR) $(OUT_DIR) $(STATIC_DIR) $(DYNAMIC_DIR) $(O_EXT_DIR)

# Compiler
CC			= @gcc
LANG_EXT	= c
HEADER_EXT	= h
OBJ_EXT		= o
FLAGS		= -Wall -fPIC -I$(INCLUDE_DIR)
SHARED_FLAG	= -shared

# 
AR			= @ar
AR_FLAGS	= cvq

# Commands
ECHO		= @echo
COPY		= @cp
MOVE		= @mv
MAKEDIR		= @mkdir
REMOVE		= @rm


all: static_lib dynamic_lib
	$(ECHO) "Done\n"

install: #static_lib dynamic_lib
	$(ECHO) "Not supported yet"

clean:
	$(REMOVE) -rf $(FOLDERS)


static_lib: make_objects make_extra_objects ar_static_lib ar_static_extra_lib
	$(ECHO) "\tStatic library done\n"

dynamic_lib: make_objects make_extra_objects compile_dynamic_lib compile_dynamic_extra_lib
	$(ECHO) "\tDynamic library done\n"


makefolders:
	$(ECHO) "Making folders"
	$(MAKEDIR) -p $(FOLDERS)
	$(ECHO) "\tFolders done\n"


make_objects: makefolders
	$(ECHO) "Making objects"
	$(CC) -c $(SRC_DIR)/*.$(LANG_EXT) $(FLAGS)
	$(ECHO) "->Moving files"
	$(MOVE) *.$(OBJ_EXT) $(OBJ_DIR)/
	$(ECHO) "\tObjects done\n"

make_extra_objects: makefolders
	$(ECHO) "Making extra objects"
	$(CC) -c $(SRC_DIR)/$(EXTRA_DIR)/*.$(LANG_EXT) $(FLAGS)
	$(ECHO) "->Moving files"
	$(MOVE) *.$(OBJ_EXT) $(O_EXT_DIR)/
	$(ECHO) "\tExtra objects done\n"


ar_static_lib: make_objects
	$(ECHO) "Making static lib"
	$(AR) $(AR_FLAGS) $(STATIC_DIR)/$(STC_LIB_PRE)$(LIB_NAME).$(STC_LIB_EXT) $(OBJ_DIR)/*.$(OBJ_EXT)
	$(ECHO) "->Static lib done"

compile_dynamic_lib: make_objects
	$(ECHO) "Making dynamic lib"
	$(CC) $(OBJ_DIR)/*.$(OBJ_EXT) $(SHARED_FLAG) -o $(DYNAMIC_DIR)/$(DYN_LIB_PRE)$(LIB_NAME).$(DYN_LIB_EXT)
	$(ECHO) "->Dynamic lib done"

ar_static_extra_lib: make_extra_objects
	$(ECHO) "Making static extra lib"
	$(AR) $(AR_FLAGS) $(STATIC_DIR)/$(STC_LIB_PRE)$(LIB_NAME)_extra.$(STC_LIB_EXT) $(O_EXT_DIR)/*.$(OBJ_EXT)
	$(ECHO) "->Static extra lib done"

compile_dynamic_extra_lib: make_extra_objects
	$(ECHO) "Making dynamic extra lib"
	$(CC) $(O_EXT_DIR)/*.$(OBJ_EXT) $(SHARED_FLAG) -o $(DYNAMIC_DIR)/$(DYN_LIB_PRE)$(LIB_NAME)_extra.$(DYN_LIB_EXT)
	$(ECHO) "->Dynamic lib done"
