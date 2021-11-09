from django.shortcuts import render
from rest_framework.views import APIView
from .models import TestResultRecord
from rest_framework.response import Response
from .serializer import TestResultRecordSerializer
from rest_framework import status


# Create your views here.
class TestResultView(APIView):
	"""
	A class based view for fetching TestResult Record with postId.
	"""
	def post(self, request):
		ids = [1, 2, 3, 4, 5, 1, 1, 2, 4, 3]
		studentNames = ["Vic", "Isabella", "Tommy", "Sara", "Peggy", "Wendy", "Veronika", "Karl", "Cindy", "Peter"]
		results = [3.1, 100, 2.5, 60.2, 70.5, 82.2, 39.2, 93.2, 74.3, 10.9]

		for i in range(len(ids)):
			curId = ids[i]
			curStudentName = studentNames[i]
			curResult = results[i]
			testResultRecord = TestResultRecord(testId=curId, studentName=curStudentName, result=curResult)
			testResultRecord.save()
		response = Response(status=status.HTTP_201_CREATED)
		return response

	def get(self, request, givenTestId):
		"""
		Get all student's test result based on given testId
    	Parameters: testId
    	--------------
    	request: json format
        		Data containing request information, or None
				Returns
    	--------------
    	response: json format
        		testResultRecord of the given index
		"""
		testResultRecords = TestResultRecord.objects.all().filter(testId=givenTestId)
		text = []
		for trr in testResultRecords:
			text.append(TestResultRecordSerializer(trr).data)

		response = Response(
			text,
            status=status.HTTP_200_OK)
		response["Access-Control-Allow-Origin"] = "*"
		return response
