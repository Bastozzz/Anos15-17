--EX1----------
select *
from AUTORES;

--EX2----------
select TITULO
from LIVROS;

--EX3----------
select distinct GENERO
from LIVROS;

--EX4----------
select TITULO
from LIVROS
where PRECO_TABELA between 25 and 35;

--EX5----------
select CODIGO_LIVRO , TITULO
from LIVROS
where LIVROS.GENERO = 'Informática';

--EX6----------
select TITULO
from LIVROS
where LIVROS.PAGINAS > 500 and LIVROS.GENERO = 'Policial';

--EX7----------
select distinct GENERO
from LIVROS
where LIVROS.PAGINAS > 700 or LIVROS.PRECO_TABELA > 45;

--EX8----------
select TITULO, PRECO_TABELA
from LIVROS
where LIVROS.GENERO = 'Informática'
order by PRECO_TABELA desc;

--EX9----------
select ISBN, TITULO, PRECO_TABELA, QUANT_EM_STOCK
from LIVROS
where GENERO = 'Informática'
order by PRECO_TABELA desc, QUANT_EM_STOCK asc;

--EX10---------
select distinct CODIGO_AUTOR
from LIVROS
where QUANT_EM_STOCK > 0;

--EX11---------
select titulo
from livros
where genero != 'Policial';

--EX12---------
select titulo
from livros
where not genero = 'Policial';

--EX13---------
select NOME
from AUTORES
where IDADE > 30 and GENERO_PREFERIDO = 'Policial'
order by NOME;

--EX14---------
select NOME
from AUTORES
where NOME LIKE '%r%' and NOME LIKE '%d%';

--EX15---------
select TITULO
from LIVROS
where TITULO like 'O%' and TITULO like '%st%' or 
      TITULO like 'M%' and TITULO like '%to%';
      
--EX16---------
select TITULO
from LIVROS
where GENERO = 'Policial' or genero = 'Romance' or genero = 'Aventura';

--EX17---------
select 'O livro "' || TITULO || '" custa ' || 
       PRECO_TABELA || ' euros' as "Listagem de Livros"
from LIVROS;

