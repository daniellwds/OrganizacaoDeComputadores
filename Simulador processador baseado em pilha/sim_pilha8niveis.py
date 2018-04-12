'''
Nome: Daniel Luis Welter da Silva
'''

import os

def readExpression():
    stringExpression = ''
    while stringExpression == '':
        stringExpression = input("\nDigite a expressão em Notação Polonesa Inversa:\n")

    listExpression = stringExpression.split()
    return listExpression


def stackFunction(listExpression):
    stackList = []
    stackPointer = -1
    valueControl = 0

    for i in range(len(listExpression)):
        if stackPointer > 7: #garante que nunca seja maior que 8 niveis
            print ("Tamanho da pilha estourado!!\n\n")
            break
        elif listExpression[i].isdigit():
            stackPointer += 1
            stackList.append(int(listExpression[i])) #comando push
        else:
            if stackPointer > 0:
                if listExpression[i] == "+": #operação de soma
                    valueControl = stackList.pop() #comando pop
                    stackPointer -= 1
                    stackList[stackPointer] += valueControl
                elif listExpression[i] == "-": #operação de subtração
                    valueControl = stackList.pop() #comando pop
                    stackPointer -= 1
                    stackList[stackPointer] -= valueControl
                elif listExpression[i] == "*" or listExpression[i] == "x": #operação de multiplicação
                    valueControl = stackList.pop() #comando pop
                    stackPointer -= 1
                    stackList[stackPointer] *= valueControl
                elif listExpression[i] == "/": #operação de divisão
                    valueControl = stackList.pop() #comando pop
                    stackPointer -= 1
                    stackList[stackPointer] /= valueControl
                else:
                    print("Não é uma operação válida! Verifique a expressão e tente novamente! \n\n")
                    break
            else:
                print("Não há numeros disponiveis suficientes para as operações aritméticas, verifique a expressão e tente novamente!")
                listExpression = readExpression()
                stackFunction(listExpression)
                break
        
       
        if stackPointer < 8: #Comando extra mostrar pilha
            auxiliarList = list(stackList)
            auxiliarList.reverse()
            print('-' + str(i + 1) + 'ª Iteração' + '\nPilha:')
            control = 8 - len(auxiliarList)

            for k in range(0, control):
                print('[ ]')
            for j in range(len(auxiliarList)):
                if j == 0:
                    print('['+ str(auxiliarList[j]) +']' + '<---Stack Pointer = ' + str(stackPointer))
                else:
                    print('[' + str(auxiliarList[j]) + ']')
            print("")

    input("Pressione ENTER para continuar")
    os.system('cls' if os.name == 'nt' else 'clear')

def menu():
    a = 0
    os.system('cls' if os.name == 'nt' else 'clear') 
    print('Processador com conjunto de instruções baseado em pilha \n')
    
    while(a != '2'):
        print('\tMENU\n1- Calcular expressão em Notação Polonesa Inversa\n2- Sair')
        a = input()

        if a == '1' :
            os.system('cls' if os.name == 'nt' else 'clear')
            listExpression = readExpression()
            stackFunction(listExpression)
        elif a != '2' :
            print('\nOPERAÇÃO INVÁLIDA!\n')

menu()