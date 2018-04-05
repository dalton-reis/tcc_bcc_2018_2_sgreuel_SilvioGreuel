# TCC1

## rogressive Web Application (PWA)

**Sobre:**

> A conceito é simples, é tornar qualquer aplicação acessível via browser, uma aplicação nativa(como no chrome-os), porém para celulares(como no firefox-os).

> Aplicações nativas podem ou não funcionar offline, mesmo vale para aplicações PWA, caso haver a necessidade de o fazer, lembrar de que uma PWA é uma aplicação web, as dificuldades serão as mesmas. 

> Como por base uma aplicação PWA é uma aplicação WEB, ela necessida de um browser para que seja executada e, não necessáriamente, todos browsers compartilham do mesmo set de features/apis.

> Navegadores são basicamente interpretadores, fazem o parsing do pedaço do script a ser executado, geram código de máquina (relacionando também o JIT), por fim o código de máquina é executado, não espere por velocidade de processamento. 

> Caso velocidade de processamento é desejado, opte por criar código em web-assembly (capacidade de trazer código compilado para o navegador) ou utilizar a capacidade de computação disponivel pela api webgl (processamento na GPU, celulares = arm), alguns navegadores em estado canario/noturno estão testando a geração de web-assembly a partir do código javascript em modo estrito(funcionalidades dinamicas são descartadas)

**Links:**
- https://whatwebcando.today/ server para checar as apis acessiveis pelo seu navegador (utilizar com o navegador do celular)
- https://pwa.rocks/ lista de aplicações PWA disponíveis atualmente
- https://www.chromestatus.com/features lista as features disponíveis pelo browser chrome
- https://platform-status.mozilla.org/ lista as features disponíveis para uma seleção de browsers
- https://hnpwa.com/ implementações de PWAs imitando o site Hacker News em varias frameworks

