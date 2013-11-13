Capitulo 1
===================
** 1.1) Quais são os três principais objetivos de um sistema operacional? **

> R.: Os três principais objetivos são: 

>    1. Proporcionar um ambiente para o suário executar seus programas no sistema de computação de maneira conveniente e eficiente;
>    2. Alocar os recursos necessários do sistema de computação para resolver algum problema ocorrido. O processo de alocação deve ser o mais eficiente possível;
>	3. Como um programa de controle que funciona duas funções principais: (1) fiscalização da execução dos programas do usuário para evitar erros e uso indevido do computad or, e (2) a gestão da operação e controle de dispositivos de E/S.

** 1.2) Temos enfatizado a necessidade de um sistema operacional para fazer  uso eficiente do computador. Em quem momento é apropriado para o sistema operacional abandonar este princípio e "desperdiçar" recursos? Por que neste caso não é realmente um desperdício? **
> R.: Sistemas de um único usuário deve maximizar o uso do sistema para o ** usuário **. A GUI pode "desperdiçar" ciclos de CPU, mas otimiza a interação do usuário com o sistema.


** 1.3) Qual é a principal dificuldade que um programador deve superar para escrever um sistema operacional para um ambiente de tempo real? **
> R.: A principal dificuldade é manter o sistema operando dentro dos limites de um sistema em tempo real em tempo fixos. Se o sistema não concluir uma tarefa em um determinado período de tempo, isso pode causar um colapso de todo o sistema que está sendo executado. Portanto, ao escrever um sistema operacional para um sistema em tempo real, o programador deve ter certeza de que sua implementação não permite que o tempo de resposta supere esta restrição de tempo.

** 1.4) Tendo em mente as diversas definições de sistema operacional, considere se o sistema operacional deve incluir aplicações como navegadores da Web e e-mail programas. Argumentar tanto que deveria e que não deveria, e apoiar suas respostas.**
> R.: Um argumento a favor da inclusão aplicativos populares a um sistema operacional é que se o pedido for incorporado ao S.O., é provável que seja mais capaz de tirar proveito dos recursos do kernel e, portanto, têm vantagens de desempenho sobre uma aplicação que não tem acesso direto ao kernel. Argumentos contra, que normalmente dominam, são: (1) as aplicações são aplicações - e não parte de um sistema operacional, (2) os benefícios de rodar dentro do kernel desempenho são compensados pela vulnerabilidades de segurança, (3) que leva a uma sistema operacional inchado.

** 1.5) Como funciona a distinção entre o modo kernel e função do modo de usuário como uma forma rudimentar de proteção (segurança) do sistema?**
> R.: A distinção entre o modo kernel e modo usuário fornece uma forma rudimentar de proteção da seguinte maneira. Certas instruções poderia ser executado somente quando a CPU está em modo kernel. Da mesma forma, os dispositivos de hardware pode ser acessado somente quando o programa está sendo executado em modo kernel. O controle em relação ao momento em que as interrupções podem ser ativados ou desativados também só é possível quando o CPU está em modo kernel. Consequentemente, a CPU tem capacidade muito limitada ao executar no modo de usuário, reforçando, assim, a proteção dos recursos críticos.

** 1.6) Quais das seguintes instruções devem ter privilégio para execução: **

    a. Definir um valor de timer
    b. Leitura do clock
    c. Limpeza de memória
    d. Gerar uma trap instruction
    e. Desligar as interrupções
    f. Modificar entradas na tabela de status dos dispositivos
    g. Trocar do modo usuário para modo kernel
    h. Acessar um dispositivo E/S
> R.: As seguintes operações devem ser privilegiadas: Definir um valor do timer, Limpeza de memória, desligar interrupções, modificar as entradas na tabela de status do dispositivo, acesso aos dispositivos de  E/S. O restante pode ser realizada em modo de usuário.

** 1.7) Alguns dos primeiros computadores protegiam seu sistema operacional colocando-o em uma divisão de memória que não poderia ser modificado por qualquer utilizador ou o trabalho do próprio sistema. Descreva duas dificuldades que você acha que poderia surgir com esse esquema.**
> R.: Os dados requeridos pelo sistema operacional (senhas, controles de acesso, e assim por diante) que têm de ser armazenados em ou transmitidos através da memória desprotegida e, assim, tornar o sistema operacional inseguro.

** 1.8) Algumas CPUs prevêem mais de dois modos de operação. Quais são os dois usos possíveis desses modos múltiplos? **
> R.: Embora a maioria dos sistemas só faz distinção entre o usuário e os modos de kernel, algumas CPUs têm apoiado vários modos. Modos múltiplos poderia ser utilizado para fornecer um mais refinado política de segurança. Por exemplo, ao invés de distinguir apenas usuário e modo kernel, você pode faz distinção entre diferentes tipos de modo de usuário. Talvez os usuários pertencentes a um mesmo grupo pode executar código do outro. A máquina iria entrar em um modo especificado quando um desses usuários foi a execução de código. Quando a máquina foi neste modo, um membro do grupo pode executar o código pertencente a qualquer outra pessoa no grupo.

>   Outra possibilidade seria a de fornecer diferentes distinções no código do kernel. Por exemplo, um modo específico pode permitir que drivers de dispositivos USB para funcionar. Isso significaria que os dispositivos USB poderia ser atendido sem ter que mudar para o modo kernel, assim, essencialmente permitindo que drivers de dispositivos USB para funcionar em um modo semi usuário/kernel.

** 1.9) Timers poderia ser usado para calcular a hora atual. Forneça uma breve descrição de como isso poderia ser feito.**
> R.: Um programa pode usar a seguinte abordagem para calcular a hora atual usando interrupções do timer. O programa pode definir um temporizador para algum momento no futuro e ir dormir. Quando ele é despertado pela interrupção, pode atualizar seu estado local, que ele está usando para controlar o número de interrupções que recebeu até agora. Ele poderia, então, repetir este processo de criação contínua interrupções do timer e atualizar seu estado local quando as interrupções são realmente levantado.

** 1.10) Dê duas razões pelas quais caches são úteis. Quais os problemas que eles resolvem? Quais os problemas que eles causam? Se um cache pode ser feito tão grande como o dispositivo para o qual ele é cache (por exemplo, um cache tão grande como a de um disco), porque não torná-lo tão grande e eliminar o dispositivo?**
> R.: Caches são úteis quando dois ou mais componentes precisam trocar dados, e os componentes realizar transferências em diferentes velocidades. Caches resolver o problema de transferência, proporcionando um tampão de velocidade intermédia entre os componentes. Se o dispositivo rápido encontra os dados de que necessita no cache, ele não precisa esperar para o dispositivo mais lento. Os dados no cache deve ser mantido de acordo com os dados dos componentes. Se um componente tem uma alteração do valor de dados, e os dados também está no cache, o cache também deve ser atualizado. Este é um problema especialmente em sistemas multiprocessados, onde mais de um processo pode estar acessando um dado. Um componente pode ser eliminado por um cache de tamanho igual, mas somente se: (a) o componente de cache e tem capacidade equivalente de poupança de estado (isto é, se o componente retém os dados, quando a carga é removida, o cache deve reter dados bem), e (b) a memória cache é acessível, porque o armazenamento mais rápido tende a ser mais caro.

** 1.11) Distinguir entre os modelos cliente-servidor e ponto-a-ponto de sistemas distribuídos.**
> R.: O modelo cliente-servidor distingue firmemente os papéis de cliente e servidor. De acordo com este modelo, o cliente solicita serviços que são prestados pelo servidor. O modelo ponto a ponto não tem papéis tão rígidas. Na verdade, todos os nós do sistema são considerados pares e, portanto, pode atuar como clientes ou servidores, ou ambos. Um nó pode solicitar um serviço de outro par, ou o nó pode, de facto, prestar esse serviço para outros pontos do sistema.

>   Por exemplo, vamos considerar um sistema de nós que compartilham receitas de cozinha. Sob o modelo cliente-servidor, todas as receitas são armazenados no servidor. Se um cliente deseja acessar uma receita, deverá solicitar a receita do servidor especificado. Usando o modelo ponto a ponto, um nó de pares poderia pedir outros nós pares para a receita especificada. O nó (ou talvez nós) com a receita solicitada poderia fornecer ao nó requerente. 
Observe como cada peer pode atuar como um cliente (que pode solicitar receitas) e como servidor (que pode fornecer receitas).