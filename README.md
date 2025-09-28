# 🐚 **Proyecto minishell** 🚀

El **proyecto minishell** es un reto de 42 en el que debes crear tu propia shell desde cero en C.  
🧑‍💻 El objetivo es entender cómo funciona una shell real: ejecutar comandos, gestionar procesos, redirecciones, pipes, variables de entorno y señales.

---

## ✨ **Lo que aprenderás realizando el proyecto**

A lo largo de minishell, adquirirás conocimientos clave para el desarrollo de utilidades de sistema y la gestión avanzada de procesos en C:

- 🖥️ **Ejecución de comandos y builtins**  
  Implementarás la ejecución de comandos externos y funciones internas como `cd`, `echo`, `pwd`, `env`, `export`, `unset` y `exit`.

- 🔗 **Gestión de pipes y redirecciones**  
  Aprenderás a crear y gestionar **pipes** (`|`) para conectar procesos, y a implementar redirecciones (`>`, `<`, `>>`, `<<`) para controlar la entrada y salida de los comandos.

- 🌱 **Variables de entorno y expansión**  
  Trabajarás con el entorno del sistema, permitiendo la expansión de variables (`$VAR`, `$?`) y la modificación dinámica del entorno.

- 🧩 **Parsing y análisis sintáctico**  
  Desarrollarás lógica para **parsear** la línea de comandos, gestionar comillas, operadores y construir la estructura interna de los comandos.

- 🛡️ **Gestión de señales y errores**  
  Implementarás el manejo de señales como `SIGINT` y `SIGQUIT`, y te asegurarás de que la shell gestione correctamente los errores y la memoria.

- 📚 **Uso de librerías propias (libft)**  
  Integrarás funciones de tu propia librería (**libft**) para facilitar el manejo de cadenas, listas y utilidades varias.

---

## 🏁 **El resultado final**

El resultado será una **shell funcional** capaz de ejecutar comandos, gestionar pipes y redirecciones, expandir variables de entorno y responder a señales como lo haría una shell real.  
Este proyecto te dará una base sólida para comprender el funcionamiento interno de sistemas operativos y shells.

---

## ⚡ **Ejemplo de uso**

```sh
./minishell
```

```sh
ls -l | grep minishell > salida.txt
echo $HOME
export VAR=42
cat << EOF
Texto heredoc
EOF
```

---

## 🛠️ **Compilación**

```sh
make
```

Esto generará el ejecutable `minishell` en el directorio raíz.

---

## 📁 **Estructura del proyecto**

```
minishell/
├── inc/                # Cabeceras (.h)
├── libft/              # Librería auxiliar libft
├── src/                # Código fuente organizado por módulos
├── Makefile
└── documentacion/
```