Main.exe: IndexBuffer.o Main.o Renderer.o Shader.o Texture.o VertexArray.o VertexBuffer.o stb_image.o
		g++ -o Main.exe IndexBuffer.o Main.o Renderer.o Shader.o Texture.o VertexArray.o VertexBuffer.o stb_image.o -lglfw3dll -lopengl32 -lglew32

IndexBuffer.o: IndexBuffer.cpp
	g++ -c IndexBuffer.cpp
Main.o: Main.cpp
	g++ -c Main.cpp
Renderer.o: Renderer.cpp
	g++ -c Renderer.cpp
Shader.o: Shader.cpp
	g++ -c Shader.cpp
Texture.o: Texture.cpp
	g++ -c Texture.cpp
VertexArray.o: VertexArray.cpp
	g++ -c VertexArray.cpp
VertexBuffer.o: VertexBuffer.cpp
	g++ -c VertexBuffer.cpp
stb_image.o: vendor/stb_image/stb_image.cpp
	g++ -c vendor/stb_image/stb_image.cpp
	
clean:
	rm *.o