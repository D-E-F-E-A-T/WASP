compile:
	gcc main.c mesh_loader.c shader_loader.c glad.c vutilities.c -lglfw -lGL -lGLU -lX11 -ldl 

run:
	./a.out