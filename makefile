
SRCDIR := src
BUILDDIR := .build
INTDIR := $(BUILDDIR)/obj
OUTPUT := OP2BitmapConverter
UTILITYBASE := OP2Utility
UTILITYDIR := OP2Utility
UTILITYLIB := $(UTILITYDIR)/lib$(UTILITYBASE).a

CPPFLAGS := -I $(UTILITYDIR)/include
CXXFLAGS := -std=c++17 -g -Wall -Wno-unknown-pragmas
LDFLAGS := -L$(UTILITYDIR)
LDLIBS := -l$(UTILITYBASE) -lstdc++fs -lstdc++ -lm

DEPFLAGS = -MT $@ -MMD -MP -MF $(INTDIR)/$*.Td

COMPILE.cpp = $(CXX) $(DEPFLAGS) $(CPPFLAGS) $(CXXFLAGS) $(TARGET_ARCH) -c
POSTCOMPILE = @mv -f $(INTDIR)/$*.Td $(INTDIR)/$*.d && touch $@

SRCS := $(shell find $(SRCDIR) -name '*.cpp')
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(INTDIR)/%.o,$(SRCS))
FOLDERS := $(sort $(dir $(SRCS)))

all: $(OUTPUT)

.PHONY: op2utility
op2utility:
	$(MAKE) -C $(UTILITYDIR)

$(OUTPUT): $(OBJS) | op2utility
	@mkdir -p ${@D}
	$(CXX) $^ $(LDFLAGS) -o $@ $(LDLIBS)

$(OBJS): $(INTDIR)/%.o : $(SRCDIR)/%.cpp $(INTDIR)/%.d
	@mkdir -p ${@D}
	$(COMPILE.cpp) $(OUTPUT_OPTION) $<
	$(POSTCOMPILE)

$(INTDIR)/%.d: ;
.PRECIOUS: $(INTDIR)/%.d

include $(wildcard $(patsubst $(SRCDIR)/%.cpp,$(INTDIR)/%.d,$(SRCS)))

.PHONY: clean clean-all
clean:
	-rm -rf $(INTDIR)
clean-all:
	-rm -rf $(BUILDDIR)
	$(MAKE) -C $(UTILITYDIR) clean-all


.PHONY: check
check:
	@echo "No tests to run"
