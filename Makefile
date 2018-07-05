CC			= gcc
LANG_EXT	= c
HEADER_EXT	= h
OBJ_EXT		= o
FLAGS		= -Wall -fPIC
SHARED_FLAG	= -shared

SRC_DIR		= src
OBJ_DIR		= obj
HEADER_DIR	= header
EXTRA_DIR	= extra
OUT_DIR		= out
O_EXT_DIR	= $(OBJ_DIR)/$(EXTRA_DIR)
STATIC_DIR	= $(OUT_DIR)/static
DYNAMIC_DIR	= $(OUT_DIR)/dynamic
LIB_DIR		= lib
INCLUDE_DIR	= include
STC_LIB_DIR	= $(STATIC_DIR)/$(LIB_DIR)
STC_INC_DIR	= $(STATIC_DIR)/$(INCLUDE_DIR)
DYN_LIB_DIR	= $(DYNAMIC_DIR)/$(LIB_DIR)
DYN_INC_DIR	= $(DYNAMIC_DIR)/$(INCLUDE_DIR)

AR			= ar
AR_FLAGS	= cvq
LIB_NAME	= ALF_std


DIRECTORIES	= bool dict IO str
EXTRA_DIRS	= dso_loader
FOLDERS		= $(OBJ_DIR) $(HEADER_DIR) $(OUT_DIR) $(STATIC_DIR) $(DYNAMIC_DIR) $(O_EXT_DIR) $(STC_LIB_DIR) $(STC_INC_DIR) $(DYN_LIB_DIR) $(DYN_INC_DIR)


ECHO		= @echo
COPY		= cp
MOVE		= mv
MAKEDIR		= mkdir
REMOVE		= rm


all: static_lib dynamic_lib
	$(ECHO) "->Done"

install: #static_lib dynamic_lib
	$(ECHO) "Not supported yet"

clean:
	$(REMOVE) -rf $(FOLDERS)

static_lib: makefolders make_objects make_extra_objects ar_static_lib ar_static_extra_lib create_lib_header
	$(ECHO) "->Static library done"

dynamic_lib: makefolders make_objects make_extra_objects compile_dynamic_lib compile_dynamic_extra_lib create_extra_lib_header
	$(ECHO) "->Dynamic library done"

makefolders:
	$(ECHO) "->Making folders"
	$(MAKEDIR) -p $(FOLDERS)


make_objects: $(DIRECTORIES)
	$(ECHO) "->Objects done"

make_extra_objects: $(addprefix extra_,$(EXTRA_DIRS))
	$(ECHO) "->Extra objects done"

%:
	$(ECHO) "->Making objects"
	$(CC) -c $(SRC_DIR)/$@/*.$(LANG_EXT) $(FLAGS)
	$(ECHO) "->Moving files"
	$(MOVE) *.$(OBJ_EXT) $(OBJ_DIR)/
	$(COPY) $(SRC_DIR)/$*/*.$(HEADER_EXT) $(STC_INC_DIR)/
	$(COPY) $(SRC_DIR)/$*/*.$(HEADER_EXT) $(DYN_INC_DIR)/

extra_%:
	$(ECHO) "->Making extra objects"
	$(CC) -c $(SRC_DIR)/$*/*.$(LANG_EXT) $(FLAGS)
	$(ECHO) "->Moving files"
	$(MOVE) *.$(OBJ_EXT) $(O_EXT_DIR)/
	$(COPY) $(SRC_DIR)/$*/*.$(HEADER_EXT) $(STC_INC_DIR)/
	$(COPY) $(SRC_DIR)/$*/*.$(HEADER_EXT) $(DYN_INC_DIR)/

ar_static_lib: make_objects
	$(ECHO) "->Making static lib"
	$(AR) $(AR_FLAGS) $(STC_LIB_DIR)/lib$(LIB_NAME).a $(OBJ_DIR)/*.$(OBJ_EXT)

compile_dynamic_lib: make_objects
	$(ECHO) "->Making dynamic lib"
	$(CC) $(OBJ_DIR)/*.$(OBJ_EXT) $(SHARED_FLAG) -o $(DYN_LIB_DIR)/lib$(LIB_NAME).so

ar_static_extra_lib: make_objects
	$(ECHO) "->Making static lib"
	$(AR) $(AR_FLAGS) $(STC_LIB_DIR)/lib$(LIB_NAME)_extra.a $(O_EXT_DIR)/*.$(OBJ_EXT)

compile_dynamic_extra_lib: make_objects
	$(ECHO) "->Making dynamic lib"
	$(CC) $(O_EXT_DIR)/*.$(OBJ_EXT) $(SHARED_FLAG) -o $(DYN_LIB_DIR)/lib$(LIB_NAME)_extra.so



header_head:
	$(REMOVE) -f $(HEADER_DIR)/$(LIB_NAME).$(HEADER_EXT)
	$(ECHO) "#ifndef ALF_std_h" >> $(HEADER_DIR)/$(LIB_NAME).$(HEADER_EXT)
	$(ECHO) "#define ALF_std_h" >> $(HEADER_DIR)/$(LIB_NAME).$(HEADER_EXT)
	$(ECHO) "" >> $(HEADER_DIR)/$(LIB_NAME).$(HEADER_EXT)

%.$(HEADER_EXT):
	$(ECHO) "#include \"ALF_$@\"" >> $(HEADER_DIR)/$(LIB_NAME).$(HEADER_EXT)

create_lib_header: header_head $(addsuffix .$(HEADER_EXT),$(DIRECTORIES))
	$(ECHO) "" >> $(HEADER_DIR)/$(LIB_NAME).$(HEADER_EXT)
	$(ECHO) "#endif" >> $(HEADER_DIR)/$(LIB_NAME).$(HEADER_EXT)
	$(ECHO) "" >> $(HEADER_DIR)/$(LIB_NAME).$(HEADER_EXT)
	$(COPY) $(HEADER_DIR)/$(LIB_NAME).$(HEADER_EXT) $(STC_INC_DIR)/
	$(COPY) $(HEADER_DIR)/$(LIB_NAME).$(HEADER_EXT) $(DYN_INC_DIR)/


extra_header_head:
	$(REMOVE) -f $(HEADER_DIR)/$(LIB_NAME).$(HEADER_EXT)
	$(ECHO) "#ifndef ALF_std_extra_h" >> $(HEADER_DIR)/$(LIB_NAME)_extra.$(HEADER_EXT)
	$(ECHO) "#define ALF_std_extra_h" >> $(HEADER_DIR)/$(LIB_NAME)_extra.$(HEADER_EXT)
	$(ECHO) "" >> $(HEADER_DIR)/$(LIB_NAME)_extra.$(HEADER_EXT)

%.$(HEADER_EXT)_extra:
	$(ECHO) "#include \"ALF_$*\"" >> $(HEADER_DIR)/$(LIB_NAME)_extra.$(HEADER_EXT)

create_extra_lib_header: extra_header_head $(addsuffix .$(HEADER_EXT)_extra,$(EXTRA_DIRS))
	$(ECHO) "" >> $(HEADER_DIR)/$(LIB_NAME)_extra.$(HEADER_EXT)
	$(ECHO) "#endif" >> $(HEADER_DIR)/$(LIB_NAME)_extra.$(HEADER_EXT)
	$(ECHO) "" >> $(HEADER_DIR)/$(LIB_NAME)_extra.$(HEADER_EXT)
	$(COPY) $(HEADER_DIR)/$(LIB_NAME)_extra.$(HEADER_EXT) $(STC_INC_DIR)/
	$(COPY) $(HEADER_DIR)/$(LIB_NAME)_extra.$(HEADER_EXT) $(DYN_INC_DIR)/


