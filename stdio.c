// #include <stdio.h>

long syscall(long number, long arg1, long arg2, long arg3)
{
  long ret;
  __asm__ volatile("syscall"
                   : "=a"(ret)
                   : "a"(number), "D"(arg1), "S"(arg2), "d"(arg3)
                   : "rcx", "r11", "memory");
  return ret;
}

long write(long fd, const char *buf, long count)
{
  return syscall(1, fd, (long)buf, count);
}

void itoa(int n, char *str)
{
  unsigned int num;
  int i = 0;

  // Handle negative numbers
  if (n < 0)
  {
    str[i++] = '-';
    // Convert to positive safely, including INT_MIN
    num = (unsigned int)(-(long)n);
  }
  else
  {
    num = (unsigned int)n;
  }

  // Count digits
  int start = i;
  unsigned int temp = num;
  if (temp == 0)
  {
    str[i++] = '0';
    str[i] = '\0';
    return;
  }
  while (temp > 0)
  {
    temp /= 10;
    i++;
  }

  str[i] = '\0'; // Null terminator
  i--;

  // Fill digits from the end
  while (num > 0)
  {
    str[i--] = '0' + (num % 10);
    num /= 10;
  }
}

void ftoa(float n, char *str, int precision)
{
  int i = 0;

  // sign
  if (n < 0)
  {
    str[i++] = '-';
    n = -n;
  }

  // integer part
  int ip = (int)n;
  float fp = n - ip;

  // int → str (inline)
  char tmp[16];
  int j = 0;
  if (ip == 0)
    tmp[j++] = '0';
  while (ip > 0)
  {
    tmp[j++] = '0' + (ip % 10);
    ip /= 10;
  }
  while (j--)
    str[i++] = tmp[j];

  // decimal point
  if (precision > 0)
    str[i++] = '.';

  // fractional part
  while (precision--)
  {
    fp *= 10;
    int d = (int)fp;
    str[i++] = '0' + d;
    fp -= d;
  }

  str[i] = '\0';
}

int my_strlen(const char *str)
{

  int len = 0;
  while (str[len] != '\0')
  {
    len++;
  }
  return len;
}

void my_printf(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  while (*format)
  {
    if (*format == '%')
    {
      format++;
      if (*format == 'd')
      {
        int val = va_arg(args, int);
      }
    }
  }
  // write(1, format, my_strlen(format));
}

int main()
{

  my_printf("Hello, World!\n");
  return 0;
}
