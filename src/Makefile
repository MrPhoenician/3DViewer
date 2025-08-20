SHELL = /bin/sh

DIST_FILES := $(wildcard desktop/*.cpp) \
             $(wildcard desktop/*.h) \
             $(wildcard desktop/*.pro) \
             $(wildcard dependencies/*.h) \
             $(wildcard model/*.cpp) \
             $(wildcard model/*.h) \
             $(wildcard api/*.cpp) \
             $(wildcard api/*.h) \
             $(wildcard shaders/) \
             $(wildcard tests/*.cpp) \
             $(wildcard tests/*.h) \
             $(wildcard controller/*.h) \
             $(wildcard controller/*.cpp) \
             Makefile \
             main.cpp

all: 3DViewer
.PHONY: all

3DViewer:
	cd desktop && qmake6 desktop.pro && make && make clean && rm Makefile .qmake.stash && mv 3DViewer ../
	./3DViewer
.PHONY: 3DViewer

run:
	./3DViewer

install:
	mkdir -p ~/3DViewer_v2_from_HRB/
	install ./3DViewer ~/3DViewer_v2_from_HRB/
.PHONY: install

uninstall:
	rm ~/3DViewer_v2_from_HRB/3DViewer
	rmdir ~/3DViewer_v2_from_HRB/
	rm -rf ~/.config/S21/3DViewer.conf
.PHONY: uninstall

clean:
	rm -rf out/*.* html_report dvi/ docdir/ bindir/ *.tar.gz test *.info *.gcda *.gcno desktop/*.o desktop/.qmake.stash \
	desktop/Makefile desktop/moc_*.* ~/.config/S21/3DViewer.conf desktop/*.gcda desktop/*.gcno desktop/3DViewer_test
.PHONY: clean

dvi:
	open ./README.md
.PHONY: dvi

dist:
	@rm -f 3DViewer_dist.tar.gz
	@tar -czf 3DViewer_dist.tar.gz --transform 's,^\./,3DViewer/,' $(DIST_FILES)
.PHONY: dist

tests: clean
	cd desktop && qmake desktop.pro "CONFIG+=test" && make && make clean && rm Makefile .qmake.stash && ./3DViewer_test
.PHONY: tests

dependences:
	sudo apt update
	sudo apt install libglew-dev
	sudo apt install libglm-dev
	sudo apt install qtcreator
	sudo apt install build-essential
	sudo apt install latexmk
	sudo apt install imagemagick
	sudo apt install qt6-declarative-dev
	sudo apt install libqt6openglwidgets6-dev
	sudo apt install libqt6opengl6-dev
	#sudo apt install gcov-14
.PHONY: dependences

clang:
	clang-format -i desktop/*.cpp desktop/*.h model/*.cpp model/*.h api/*.cpp api/*.h shaders/*.glsl tests/*.cpp tests/*.h controller/*.cpp controller/*.h
.PHONY: clang

clang_check:
	clang-format -n desktop/*.cpp desktop/*.h model/*.cpp model/*.h api/*.cpp api/*.h tests/*.cpp tests/*.h controller/*.cpp controller/*.h
.PHONY: clang_check

gcov_report: tests
	-rm -rf report/
	-lcov --rc branch_coverage=1 \
		--ignore-errors mismatch,inconsistent,version,empty \
		--rc geninfo_unexecuted_blocks=1 \
		--rc geninfo_gcov_tool='/usr/bin/gcov-14' \
		-t "s21_3DViewer_report" \
		-o s21_3DViewer_report_all.info -c -d desktop/
	-lcov --rc branch_coverage=1 \
		--ignore-errors empty \
		-r s21_3DViewer_report_all.info \
		"*/usr/*" "*src/tests*" "*src/api*" "*src/dependencies*" "*model/ObjLoader.h*" \
		-o s21_3Dviewer.info
	-genhtml --rc branch_coverage=1 -o report s21_3Dviewer.info
	@-make clean