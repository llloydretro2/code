import math
import sympy

def vectorGenerator(point1, point2):
    vector = [point1[0]-point2[0], point1[1]-point2[1], point1[2]-point2[2]]
    return vector

def prallelogramCalculator(point1, point2, point3, point4):
    vec1 = vectorGenerator(point1, point2)
    vec2 = vectorGenerator(point1, point3)
    vec3 = vectorGenerator(point1, point4)
    vec4 = matrix33Caldulator(vec1, vec2)
    result = vectorDotProduct(vec4, vec3)

    print(sum(result))

def triangleAreaCalculator(point1, point2, point3):
    vec1 = vectorGenerator(point1, point2)
    vec2 = vectorGenerator(point2, point3)
    vec3 = matrix33Caldulator(vec1, vec2)
    result = vec3[0]*vec3[0] + vec3[1]*vec3[1] + vec3[2]*vec3[2]
    print('sqrt(', result, ") / 2")

def matrix33Caldulator(point1, point2, point3):
    vec1 = vectorGenerator(point1, point2)
    vec2 = vectorGenerator(point2, point3)
    result = [vec1[1]*vec2[2]-vec1[2]*vec2[1],
              -(vec1[0]*vec2[2]-vec1[2]*vec2[0]),
              vec1[0]*vec2[1]-vec1[1]*vec2[0]]
    return result

def matrix33Caldulator(vec1, vec2):
    result = [vec1[1]*vec2[2]-vec1[2]*vec2[1],
              -(vec1[0]*vec2[2]-vec1[2]*vec2[0]),
              vec1[0]*vec2[1]-vec1[1]*vec2[0]]
    return result

def equationCal(point1, point2, point3):
    directionVec = matrix33Caldulator(point1, point2, point3)
    returnString = str(directionVec[0]) + 'x + ' + str(directionVec[1]) + 'y + ' + str(directionVec[2]) + 'z = '
    temp = 0
    for i in range(0, len(directionVec)):
        temp += directionVec[i] * point1[i]

    returnString += str(temp)
    return returnString

def vectorDotProduct(vec1, vec2):
    vector = [vec1[0]*vec2[0], vec1[1]*vec2[1], vec1[2]*vec2[2]]
    return vector

if __name__ == '__main__':
    point1 = [5, 5, -2]
    point2 = [-3, 1, -5]
    point3 = [-4, -5, 4]

    vec1 = [1, 3, 3]
    vec2 = [-3, -2, -2]

    print(matrix33Caldulator(vec1, vec2))