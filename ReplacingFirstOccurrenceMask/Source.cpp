#include <iostream>
void FindMaskRec(bool wasstar, int i, int j);
void FindMask(int i);
void masksize();
int inpsize(int i);
void Replace();

char mask[255];
char input[255];
char newinp[255];
char replace[255];
int ms;
int res = -1;

int main()
{
	std::cout << "String: ";
	std::cin.getline(input, 255);
	std::cout << "Mask: ";
	std::cin.getline(mask, 255);
	std::cout << "Replace to: ";
	std::cin.getline(replace, 255);
	masksize();
	FindMask(0);
	Replace();
	std::cout << "Result: " << newinp;
}

void Replace()
{
	if (res != -1)
	{
		int i = 0, j = 0, k = 0;
		while (input[i] != '\0')
		{
			if (i == res)
			{
				int inps = inpsize(i);
				i += inps - 1;
				while (replace[k] != '\0')
				{
					newinp[j] = replace[k];
					k++;
					j++;
				}
				j--;
			}
			else
				newinp[j] = input[i];
			i++;
			j++;
		}
		newinp[j] = '\0';
	}
	else
	{
		int i = 0;
		while (input[i] != '\0')
		{
			newinp[i] = input[i];
			i++;
		}
		newinp[i] = '\0';
	}
}

void FindMaskRec(bool wasstar, int i, int j)
{
	if (input[i] == '\0' || input[i] == ' ')
	{
		while (mask[j] != '\0')
		{
			if (mask[j] != '*')
			{
				if (input[i] == ' ') FindMask(i + 1);
				else res = -1;
			}
			j++;
		}
	}
	else if (mask[j] == '\0')
	{
		if (mask[j - 1] != '*')
		{
			while (input[i] != ' ' && input[i] != '\0') i++;
			if (input[i] == ' ') FindMask(i + 1);
			else res = -1;
		}
	}
	else if (mask[j] == '*')
	{
		if (res == -1) res = i;
		FindMaskRec(true, i, j + 1);
	}
	else if (mask[j] == '?')
	{
		if (wasstar)
		{
			if (mask[j + 1] != '\0') FindMaskRec(true, i + 1, j + 1);
		}
		else
		{
			if (res == -1) res = i;
			FindMaskRec(false, i + 1, j + 1);
		}
	}
	else if (mask[j] == input[i])
	{
		if (res == -1) res = i;
		FindMaskRec(false, i + 1, j + 1);
	}
	else if (wasstar) FindMaskRec(true, i + 1, j);
	else
	{
		bool found = false;
		while (j >= 0)
		{
			if (mask[j] == '*')
			{
				found = true;
				break;
			}
			j--;
		}
		if (found) FindMaskRec(true, i + 1, j + 1);
		else
		{
			while (input[i] != ' ' && input[i] != '\0') i++;
			if (input[i] == ' ') FindMask(i + 1);
			else res = -1;
		}
	}
}

void FindMask(int i)
{
	int inps = inpsize(i);
	res = -1;
	if (ms > inps)
	{
		if (input[i + inps] == ' ')
		{
			i += inps + 1;
			FindMask(i);
		}
	}
	else FindMaskRec(false, i, 0);
}

void masksize()
{
	int i = 0;
	while (mask[i] != '\0')
	{
		if (mask[i] != '*')
			ms++;
		i++;
	}
}

int inpsize(int i)
{
	int size = 0;
	while (input[i] != ' ' && input[i] != '\0')
	{
		i++;
		size++;
	}
	return size;
}