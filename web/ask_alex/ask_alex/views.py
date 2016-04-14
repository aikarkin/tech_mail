from django.http import HttpResponse
from django.views.decorators.csrf import csrf_exempt

@csrf_exempt
def index(request):
    res = HttpResponse()
    res.write("<pre>Hello, world!\n")
    
    res.write("GET params:\n")
    for elem in request.GET.lists():
        res.write("\t" + str(elem[0]) + ": " + str(elem[1]) + "\n")
        
    res.write("POST params:\n")
    for elem in request.POST.lists():
        res.write("\t" + elem[0] + ": " + str(elem[1]) + "\n")
    
    res.write("</pre>");
            
    return res

