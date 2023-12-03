tail -n +2 ISP_temp.md >> Information-security-and-privacy.md 

pandoc -s --toc --css pandoc.css Information-security-and-privacy.md --metadata title="Information Security And Privacy" -o example1.html

SOURCES := $(shell find src -type f -name '*.md')
TARGETS := $(patsubst src/%.md,docs/%.html,$(SOURCES))