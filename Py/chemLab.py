import math
import sympy

def hPlusCal(ph):
    return math.pow(10, -ph)

def ka2Cal():
    return

def inputRounded(input):
    return

def ka1Cal(h, ka1):
    return h*h/ka1

def calAverage(list):
    return sum(list)/len(list)

def calSDV(list):
    average = calAverage(list)
    temp = 0
    for term in list:
        temp += math.pow(average - term, 2)
    return math.sqrt(temp/(len(list)-1))

def confiCal(list):
    tiralCritical = [0, 0, 6.13, 2.92, 2.352]
    return tiralCritical[len(list)]*calSDV(list)/math.sqrt(2)

def hw5ch5q3cal(chem1, chem2):
    for i in range(0, len(chem1)):
        print(chem1[i]/chem2[i], 2*chem1[i]/chem2[i], chem1[i]**2/chem2[i], '\n')

def hw6ch7kacal(initialValue, pH):
    x = sympy.Symbol('x')
    Hplus = 10**(-pH)
    # return sympy.solve(sympy.Eq(x**2 / (initialValue-x), 10**(-pH)), x)
    return Hplus**2 / (initialValue-Hplus)

def hw6ch7pHcalq13(initialValue, ka):
    x = sympy.Symbol('x')
    xValue = sympy.solve(sympy.Eq(x**2 / (initialValue-x), ka), x)[1]
    print(xValue)
    return -math.log(xValue, 10)

def hw6ch7pHcalq14(initialValue, inaccuracy):
    realValue = initialValue * inaccuracy
    print(realValue)
    # x = sympy.Symbol('x')
    # xValue = sympy.solve(sympy.Eq(x**2 / (initialValue-x), ka), x)[1]
    # print(xValue)
    print("Expected value: ", realValue**2 / (initialValue - realValue))

def hw6ch7pHcalq14b(initialValue, ka):
    x = sympy.Symbol('x')
    realValue = sympy.solve(sympy.Eq(x**2 / (initialValue), ka), x)[1]
    print("ionazation: ", realValue / initialValue * 100, "%")

def hw6ch7pHcalq15(initialValue):
    print("pH/pOH: ", -math.log(initialValue, 10), 14 + math.log(initialValue, 10))

def hw6ch7pHcalq18(initialValue, pH):
    x = 10**(pH-14)
    print(x**2 / (initialValue - x))

if __name__ == '__main__':
    # ph = [5.85, 7, 7.42]
    # ka1 = [0.0215, 0.00000000832, 0.0190]
    # ka2 = []
    # for i in range(0, len(ph)):
    #     print(hPlusCal(ph[i]))
    #     print(ka1Cal(hPlusCal(ph[i]), ka1[i]))
    #     ka2.append(ka1Cal(hPlusCal(ph[i]), ka1[i]))
    #     print('\n')
    #
    # print(calAverage(ka2))
    # print(calSDV(ka2))
    # print(confiCal(ka2))
    # chem1 = [2.92, 2.49, 2.24]
    # chem2 = [2.2, 1.6, 1.3]
    # hw5ch5q3cal(chem1, chem2)
    hw6ch7pHcalq15(0.0706)