# Usa una imagen base de C
FROM gcc:latest

# Configura el directorio de trabajo
WORKDIR /app

# Copia el código fuente a la imagen
COPY . .

# Compila tu aplicación
RUN gcc -o myapp ejemplo_1.c -lmysqlclient

# Expone el puerto en el que tu aplicación escucha (si es necesario)
EXPOSE 8080

# Comando para ejecutar la aplicación
CMD ["./myapp"]

