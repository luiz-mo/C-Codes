# Trabalhos Alg2
## Português
Trabalho da disciplina de Algortimos e Estruturas de Dados 2, ministrada pelo Prof Dr. Elias Procópio Duarte Junior

### Enunciado do Trabalho
O Pronto Socorro "Heap or Quick" é muito importante na sua comunidade, atendendo todo tipo de emergência médica. Quando chega ao Pronto Socorro, o paciente é imediatamente encaminhado para a Enfermeira Chefe da Recepção. Ela é uma senhora muito experimente e imediatamente determina a prioridade do paciente e faz seu cadastramento na Fila de Prioridades.

Programe uma Fila de Prioridades para a Enfermeira Chefe, implementando o Tipo Abstrato de Dados Heap. Cada paciente tem cadastrado nome e prioridade. As operações que devem ser disponibilizadas incluem: InicHeap, InsereHeap, RemoveHeap, Heapfy, ChecaHeap, ImprimeHeap, HeapSort (entre outras que forem necessárias). O sistema deve permitir que a Enfermeira Chefe cadastre os pacientes que chegam à UPA, que chame o próximo que vai ser atendido (removendo do Heap, RemoveHeap), que imprima todos na sala de espera, que ordene todos os pacientes de acordo com sua prioridade. Além disso, a Enfermeira Chefe costuma passear pela sala de espera monitorando os pacientes e pode atualizar a prioridade de algum paciente que piorou ou melhorou (AlteraHeap). A qualquer momento deve ser possível imprimir o Heap.

O Heap deve ser implementado em vetor, exatamente como foi visto em sala de aula. Quando executar as funções Heapfy e HeapSort deve ser reportado o número de comparações e trocas de elemento de posição que foram executadas. No Relatório descreva todas as operações implementadas. Explique sua implementação das operações, em particular as operações RemoveHeap e AlteraHeap. Faça uma interface caprichada (menu de opções) para a Enfermeira Chefe usar seu sistema.

Implemente também os algoritmos de ordenação QuickSort e SelectSort. Implemente o QuickSort usando como pivô o elemento que é a mediana entre o primeiro, meio e último elementos do (sub-)vetor. Faça uma opção no menu para gerar um vetor de números aleatórios com 1024 elementos e mostre a comparação do HeapSort com o QuickSort e o SelectSort. Qual foi melhor na prática? Para cada algoritmo mostre o número de comparações e trocas de elemento de lugar.

## English 
Project from the Data Structures and Algorithms 2 course, taught by Dr. Elias Procópio Duarte Junior.

### Project Instructions

The Emergency Room "Heap or Quick" is very important to your community, handling all kinds of medical emergencies. When a patient arrives at the Emergency Room, they are immediately sent to the Chief Reception Nurse. She is an experienced nurse and promptly determines the patient's priority and registers them in the Priority Queue.

Write a Priority Queue for the Chief Nurse, implementing the Heap Abstract Data Type (ADT). Each patient must have a name and a priority. The operations that must be available include: InitHeap, InsertHeap, RemoveHeap, Heapfy, CheckHeap, PrintHeap, HeapSort (and any other necessary ones). The system must allow the Chief Nurse to register patients arriving at the ER, call the next patient to be treated (removing them from the Heap, RemoveHeap), print all patients in the waiting room, and sort all patients according to their priority. In addition, the Chief Nurse often walks around the waiting room monitoring patients and may update the priority of a patient who worsened or improved (UpdateHeap). At any moment, it must be possible to print the Heap.

The Heap must be implemented using an array, exactly as taught in class. When performing Heapfy and HeapSort, the program must report the number of comparisons and swaps of elements carried out. In the Report, describe all implemented operations. Explain your implementation of the operations, particularly RemoveHeap and UpdateHeap. Create a well-designed interface (menu options) for the Chief Nurse to use the system.

Also implement the sorting algorithms QuickSort and SelectSort. Implement QuickSort using as pivot the element that is the median among the first, middle, and last elements of the (sub)array. Add a menu option to generate an array of 1024 random numbers and show a comparison between HeapSort, QuickSort, and SelectSort. Which one performed better in practice? For each algorithm, show the number of comparisons and swaps of elements.
