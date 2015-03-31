NUM_THREADS=50
NUM_BALLS = 100
COR = 1.0
Compiler = g++ -std=c++11
Obj = OBJ/
Src = SRC/
Exe = EXE/

Design = DOC/

Library = -Framework=OpenGL -Framework=GLUT
#Header = ball.h physics.h user_interface.h gui.h button.h datastructures.h

all: $(Obj)main.o $(Obj)Ball.o $(Obj)Button.o $(Library)

execute: exec
	$(Exe)./$< $(NUM_BALLS) $(NUM_THREADS) $(COR) 

exec:
	$(Compiler) $(Obj)main.o $(Obj)Ball.o $(Obj)Button.o -o $@ $(Library) 
	mv $@ $(Exe)


DEBUG:
	$(Compiler) -g $(Obj)main.o $(Obj)Ball.o $(Obj)Button.o $(Library) -o $@
	mv $@ $(Exe)


$(Obj)main.o: $(Src)main.cpp $(Src)Ball.h $(Src)Button.h
	$(Compiler) -c $< $(Library)
	mv main.o $(Obj)

$(Obj)Ball.o: $(Src)Ball.cpp $(Src)Ball.h
	$(Compiler) -c $< $(Library)
	mv Ball.o $(Obj)

$(Obj)Button.o: $(Src)Button.cpp $(Src)Button.h
	$(Compiler) -c $< $(Library)
	mv Button.o $(Obj)


clean:
	rm $(Exe)exec $(Obj)main.o $(Obj)Ball.o $(Obj)Button.o 
	rm $(Exe)DEBUG

Changes.pdf: $(Src)Changes.tex
	pdflatex $(Src)Changes.tex
	mv Changes.pdf $(Design)Changes.pdf

Document: Changes.pdf
	rm -rf Changes.log rm -rf Changes.aux rm - rf Changes.toc rm -rf Changes.out
	cd $(Design); xpdf Changes.pdf


