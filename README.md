# Description
Aplicação proposta pela disciplina de *Bando de Dados*, período 2021.02, pelo docente Ary Henrique Morais de Oliveira.

Os três módulos *.c implementados são melhores explicados em: [https://www.youtube.com/watch?v=ETOJ-w2eKIY](https://www.youtube.com/watch?v=ETOJ-w2eKIY)

Para compilar os *.c e rodar os executáveis:

`gcc -o [nome_exec] [nome_múdulo].c`

`./nome_exec`

## Proposta da aplicação

Utilizar o minimundo da *figura 1.2*, do slide do capítulo 01, do livro *Sistemas de Banco de Dados;  Elmasri e Navathe* para construir uma aplicação em C para manipular arquivos.

Serão 3 módulos de aplicação, uma para gerenciar a tabela **COURSE**, outra para
**SECTION** e, por fim, uma para o **GRADE_REPORT**.

A aplicação deve inserir registros coletados por meio de formulários em um arquivo
de dados (*.dat).

A aplicação deve ser capaz de permitir a atualização de algum campo e a remoção
de registros.

Ao final, deve ter uma opção para apresentar todos os dados do banco de dados,
inclusive com o usuário podendo escolher quais atributos deseja apresentar.

![minimundo](https://i.imgur.com/0Ehjhdo.png)