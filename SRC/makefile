NUM_THREAD="default"
Compiler = g++ -std=c++11
Obj = OBJ/
Src = SRC/
Exe = EXE/
#Exedir = executable/
#Design = doc/

Library = -lGL -lglui -lGLU -lglut -lpthread
#Header = ball.h physics.h user_interface.h gui.h button.h datastructures.h

all: $(Obj)main.o $(Obj)Ball.o $(Obj)Button.o $(Library)

execute: exec
	@echo $(NUM_THREAD)
	$(Exe)./$< $(NUM_THREAD)

#DEBUG: 3D_mydebug
#	@echo $(NUM_THREAD)
#	$(Exedir)./$< $(NUM_THREAD)

#DEBUG_GDB: 3D_gdb
#@echo $(NUM_THREAD)
#gdb $(Exedir)./$< $(NUM_THREAD)
#file $(Exedir)$<


exec:
	$(Compiler) $(Obj)main.o $(Obj)Ball.o $(Obj)Button.o $@
	mv $@ $(Exe)

#3D_mydebug:
#	$(Compiler) $(Objectdir)main_mydeb.o $(Objectdir)ball_mydeb.o $(Objectdir)button_mydeb.o $(Objectdir)gui_mydeb.o $(Objectdir)physics_mydeb.o $(Objectdir)user_interface_mydeb.o $(Library) -o $@
#	mv $@ $(Exedir)

#3D_gdb:
#	$(Compiler) -g $(Objectdir)main.o $(Objectdir)ball.o $(Objectdir)button.o $(Objectdir)gui.o $(Objectdir)physics.o $(Objectdir)user_interface.o $(Library) -o $@
#	mv $@ $(Exedir)


$(Obj)main.o: $(Src)main.cpp $(Src)Ball.h $(Src)Button.h
	$(Compiler) -c $< $(Library)
	mv main.o $(Obj)
#$(Objectdir)main_mydeb.o: $(Src)main.cpp $(Src)ball.h $(Src)button.h 
#	$(Compiler) -c $< $(Library) -DMYDEBUG
#	mv main.o $(Objectdir)main_mydeb.o

$(Obj)Ball.o: $(Src)Ball.cpp $(Src)Ball.h
	$(Compiler) -c $< $(Library)
	mv ball.o $(Obj)

$(Obj)Button.o: $(Src)Button.cpp $(Src)Button.h
	$(Compiler) -c $< $(Library)
	mv button.o $(Obj)

#clean:
#rm $(Exedir)3D $(Objectdir)main.o $(Objectdir)ball.o $(Objectdir)button.o $(Objectdir)gui.o $(Objectdir)physics.o $(Objectdir)user_interface.o
#rm $(Exedir)3D_mydebug $(Objectdir)main_mydeb.o $(Objectdir)ball_mydeb.o $(Objectdir)button_mydeb.o $(Objectdir)gui_mydeb.o $(Objectdir)physics_mydeb.o $(Objectdir)user_interface_mydeb.o


#generated.pdf: $(Sourcedir)design.tex
#pdflatex $(Sourcedir)design.tex
#mv design.pdf $(Design)generated.pdf

#doc: generated.pdf
#rm -rf design.log rm -rf design.aux rm - rf design.toc rm -rf design.out
#cd $(Design); xpdf generated.pdf