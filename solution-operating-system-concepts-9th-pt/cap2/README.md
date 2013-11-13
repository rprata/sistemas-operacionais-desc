Capitulo 2
===================
**2.1) Qual o propósito das chamadas de sistema?**

> R.: Chamadas de sistema permitem que os processos em nível de usuário para solicitar serviços do sistema operacional. 

**2.2) Quais são os cinco principais atividades de um sistema operacional com relação à gestão de processos?**

> R.: 

>	a. A criação e exclusão dos processos do sistema e do usuário;
 	
> 	b. A suspenção e o recomeço dos processos;

>	c. O fornecimento do mecanismo para sincronização de processos;

>	d. O fornecimento do mecanismo para a comunicação entre processos;
 	
>	e. O fornecimento de um mecanismo para a manipulação de deadlocks;

**2.3) Quais são as três principais atividades de um sistema operacional no que diz respeito
ao gerenciamento de memória?**
> R.:

>	a. Manter o controle de quais partes da memória estão sendo usados ​​e por quem;

>	b. Decidir quais processos devem ser carregados na memória quando espaço de memória se torna disponível;
 
>	c. Alocar e desalocar espaço de memória quando necessário;

**2.4) Quais são as três principais atividades de um sistema operacional com relação ao gerenciamento de armazenamento secundário?**
> R.:

>	a. Gerenciamento de espaço livre;

>	b. Alocação de armazenamento;

>	c. Escalonamento de disco;

**2.5) Qual é o propósito do interpretador de comandos? Por que é normalmente separado do kernel?**
> R.: Ele lê os comandos do usuário ou de um arquivo de comandos e os executa, normalmente transformando-os em uma ou mais chamadas do sistema. Geralmente não é parte do kernel, já que o interpretador de comandos está sujeita a alterações.

**2.6) Quais chamadas do sistema tem que ser executado por um interpretador de comandos ou shell, a fim de iniciar um novo processo?**
> R.: Em sistemas Unix, uma chamada de sistema fork seguido por uma chamada de sistema exec precisam ser executadas para iniciar um novo processo. O fork cria clones do processo corrente, enquanto a chamada exec sobrepõe um novo processo com base em um executável diferente sobre o processo de chamada.

**2.7) Qual é o propósito do programas de sistema?**
> R.: Os programas do sistema pode ser pensado como pacotes de chamadas de sistema úteis. Eles fornecem funcionalidade básica para os usuários para que os usuários não precisam escrever seus próprios programas para resolver problemas comuns.

**2.8) Qual é a principal vantagem da abordagem em camadas para o projeto do sistema? Quais são as desvantagens de usar a abordagem em camadas?**
> R.: Como em todos os casos de design modular, concepção de um sistema operacional de uma forma modular tem várias vantagens. O sistema é mais fácil de depurar e modificar porque as mudanças afetam apenas partes limitadas do sistema ao invés de tocar em todas as seções do sistema operacional. As informações são mantidas apenas onde é necessário e é acessível apenas dentro de uma área definida e restrita, de modo que todos os erros que afetam esses dados deve ser limitada a um módulo ou camada específica.

**2.9) Liste cinco serviços prestados por um sistema operacional, e explique como cada um cria conveniência para os usuários. Em que casos seria impossível para programas em nível de usuário para fornecer estes serviços? Justifique sua resposta.**
> R.:

> 	a. Execução de programa - O sistema operacional carrega o conteúdo (ou seções) de um arquivo para a memória e inicia sua execução. Um programa em nível de usuário não pode ser confiável para alocar adequadamente o tempo de CPU;

>	b. Operações de E/S - Discos, fitas, linhas seriais e outros dispositivos devem ser comunicados com um nível muito baixo. O utilizador só precisa de especificar o dispositivo e a operação a ser executada sobre ele, enquanto que o sistema converte este pedido no dispositivo ou comandos específicos do controlador. Programas em nível de usuário não pode ser confiável para acessar apenas os dispositivos que devem ter acesso e para acessá-los apenas quando eles são de outra maneira não utilizado;

>	c. Manipulação de Arquivos do Sistema - Há muitos detalhes na criação do arquivo, exclusão, alocação e atribuição de nomes que os usuários não devem ter que executar. Blocos de espaço em disco são usados ​​pelos arquivos e deve ser rastreado. Excluindo um arquivo requer a remoção das informações o nome do arquivo e liberando os blocos alocados. Proteções também deve ser verificado para garantir o acesso ao arquivo adequado. Os programas do usuário não podia garantir a adesão aos métodos de proteção, nem ser confiável para alocar apenas blocos livres e desalocar blocos na exclusão do arquivo;

>	d. Comunições - A troca de mensagens entre os sistemas exige que as mensagens sejam transformados em pacotes de informação, enviado para o controlador de rede, transmitida através de um meio de comunicação, e remontado pelo sistema de destino. Packet ordenação e correção de dados deve ter lugar. Mais uma vez, os programas de usuário não pode coordenar o acesso ao dispositivo de rede, ou eles podem receber pacotes destinados a outros processos;

>	e. Deterção de Erro - A detecção de erros ocorre tanto no nível de hardware e software. Ao nível do hardware, todas as transferências de dados devem ser inspecionados para garantir que os dados não foram corrompidos em trânsito. Todos os dados sobre a mídia deve ser examinado para ter certeza que eles não mudaram desde que foram escritos para a imprensa. Ao nível do software, meios têm de ser verificados para a consistência dos dados, por exemplo, se o número de blocos alocados armazenamento e não atribuído de corresponder ao número total do dispositivo. Lá, os erros são frequentes processo independente (por exemplo, a corrupção de dados em um disco), então deve haver um programa global (o sistema operacional), que lida com todos os tipos de erros. Além disso, por ter erros processados ​​pelo sistema operacional, os processos não precisam conter código para capturar e corrigir todos os erros possíveis em um sistema.;

**2.10) Por que alguns sistemas de armazenam o sistema operacional em firmware, enquanto outros armazenam no disco?**
> R.: Para determinados dispositivos, tais como PDAs e telefones celulares, um disco com um sistema de arquivos pode não ser estar disponível para o dispositivo. Nesta situação, o sistema operativo tem de ser armazenada no firmware.

**2.11) Como poderia um sistema seja projetado para permitir uma escolha de sistemas operacionais a partir do qual a inicializar? Qual seria o programa de inicialização precisa fazer?**
> R.: Considere um sistema que gostaria de executar o Windows XP e diferentes distribuições de Linux (por exemplo, RedHat, Debian e Mandrake). Cada sistema de operação será armazenado no disco. Durante a inicialização do sistema, um programa especial (que vamos chamar o gerenciador de boot) irá determinar qual sistema operacional iniciar. Isto significa que, em vez inicialmente a inicialização para um sistema operacional, o gerenciador de boot será executado pela primeira vez durante a inicialização do sistema. É esse gerenciador de boot que é responsável por determinar qual sistema iniciar. Normalmente os gestores inicializar deve ser armazenado em determinados locais do disco rígido para ser reconhecido durante a inicialização do sistema. Gestores de arranque muitas vezes fornecer ao usuário uma seleção de sistemas para inicializar; gestores de arranque também são normalmente concebidos para inicializar um sistema operacional padrão, se nenhuma opção for selecionada pelo usuário.