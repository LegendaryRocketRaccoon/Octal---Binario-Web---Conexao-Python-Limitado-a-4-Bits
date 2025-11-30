INTRODUÇÃO

Este trabalho apresenta o desenvolvimento de um conversor de bases 
numéricas que realiza conversões bidirecionais entre as bases Octal e 
Binária. O sistema foi implementado utilizando três tecnologias integradas:

- Linguagem C: Responsável pela lógica de conversão e validação
- Python (Flask): Servidor intermediário para comunicação
- HTML/CSS/JavaScript: Interface gráfica para o usuário

O objetivo é demonstrar não apenas o conhecimento em conversão de bases,
mas também a capacidade de integrar múltiplas linguagens em um único projeto.


Se não tiver, precisa instalar o GCC, o próprio Python, e o flask pelo terminal: pip install flask flask-cors.

Para compilar o programa em C: gcc conversor.c -o conversor

Teste exemplo: ./conversor 1 755

Iniciar o servidor python: servidor.py

Depois acessar o http://localhost:5000 que será gerado.
