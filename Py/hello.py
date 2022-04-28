for n in range(2,300):
    for i in range(2,n):
        if n%i == 0:
            break
    else:
        print("{:>4}".format(n), end='')