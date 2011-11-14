
void crosscorr(int16_t * arr1, int16_t * arr2, double * res, int length, int maxdel)
{
	double mean1, mean2;
	mean1 = mean(arr1, length);
	mean2 = mean(arr2, length);
	
	for(int del = -maxdel; i < maxdel; i++)
	{
		int num = 0;
		for(int i = 0; i < length; i++)
		{
			int j = i + del;
			if(!( (j < 0) || (j >= length) ))
			{
				num += ((arr1[i] - mean1) * (arr2[j] - mean2));
			}
		}
		
		int sum1 = 0;
		int sum2 = 0;
		for(int i = 0; i < length; i++)
		{
			sum1 += ((arr1[i] - mean1) * (arr1[i] - mean1));
			sum2 += ((arr2[i] - mean2) * (arr2[i] - mean2));
		}
		double s = sqrt(sum1 * sum2);
		res[del + maxdel] = num / s;
	}
}

int dpeak(double * arr, int length)
{
	double max = 0;
	int pos = 0;
	for(int i = 0; i < length; i++)
	{
		if(abs(arr[i]) > max)
		{
			max = abs(arr[i]);
			pos = i;
		}
	}
	return pos;
}

double mean(int16_t * arr, int length)
{
	double mean = 0;
	for(int i = 0; i < length; i++)
	{
		mean += arr[i];
	}
	return mean / length;
}

