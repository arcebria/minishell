# 🐚 **Proyecto minishell** 🚀

**Minishell** es uno de los retos más interesantes que he realizado en 42: crear mi propia shell desde cero en C.  
🧑‍💻 El objetivo era entender cómo funciona una shell real, ejecutando comandos, gestionando procesos, redirecciones, pipes, variables de entorno y señales.

---

## ✨ **Lo que aprendí realizando el proyecto**

Durante el desarrollo de minishell, adquirí conocimientos clave para la programación de sistemas y la gestión avanzada de procesos en C:

- 🖥️ **Ejecución de comandos y builtins**  
  Implementé la ejecución de comandos externos y funciones internas como `cd`, `echo`, `pwd`, `env`, `export`, `unset` y `exit`.

- 🔗 **Gestión de pipes y redirecciones**  
  Aprendí a crear y gestionar **pipes** (`|`) para conectar procesos, y a implementar redirecciones (`>`, `<`, `>>`, `<<`) para controlar la entrada y salida de los comandos.

- 🌱 **Variables de entorno y expansión**  
  Trabajé con el entorno del sistema, permitiendo la expansión de variables (`$VAR`, `$?`) y la modificación dinámica del entorno.

- 🧩 **Parsing y análisis sintáctico**  
  Desarrollé lógica para **parsear** la línea de comandos, gestionar comillas, operadores y construir la estructura interna de los comandos.

- 🛡️ **Gestión de señales y errores**  
  Implementé el manejo de señales como `SIGINT` y `SIGQUIT`, asegurando que la shell gestione correctamente los errores y la memoria.

- 📚 **Uso de librerías propias (libft)**  
  Integré funciones de mi propia librería (**libft**) para facilitar el manejo de cadenas, listas y utilidades varias.

---

## 🏁 **El resultado final**

El resultado fue una **shell funcional** capaz de ejecutar comandos, gestionar pipes y redirecciones, expandir variables de entorno y responder a señales como lo haría una shell real.  
Este proyecto me dio una base sólida para comprender el funcionamiento interno de sistemas operativos y shells.

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

Esto genera el ejecutable `minishell` en el directorio raíz.

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