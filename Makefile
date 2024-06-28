# Compilador
CXX = g++

# Opciones de compilación
CXXFLAGS = -std=c++11 -Wall

# Archivos fuente
SOURCES =  main.cpp Coleccion.cpp

# Archivos objeto generados
OBJECTS = $(SOURCES:.cpp=.o)

# Nombre del ejecutable
EXECUTABLE = main

# Regla de compilación
$(EXECUTABLE): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $^ -o $@

# Regla de compilación de objetos
%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Limpiar archivos generados
clean:
	rm -f $(EXECUTABLE) $(OBJECTS)
