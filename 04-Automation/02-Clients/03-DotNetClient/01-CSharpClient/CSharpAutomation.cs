using System;
using System.Runtime.InteropServices;
using AutomationServerTypeLibForDotNet;

public class CSharpAutomation
{
    public static void Main()
    {
        //code
        CMyMathClass objCMyMathClass = new CMyMathClass();
        IMyMath objIMyMath = (IMyMath)objCMyMathClass;
        int num1, num2, sum, sub;
        num1 = 165;
        num2 = 135;
        sum = objIMyMath.SumOfTwoIntegers(num1, num2);
        Console.WriteLine("Sum of " + num1 + " And " + num2 + " Is " + sum);
        sub = objIMyMath.SubtractionOfTwoIntegers(num1, num2);
        Console.WriteLine("Sum of " + num1 + " And " + num2 + " Is " + sub);
    }
}
//csc.exe /r:AutomationServerTypeLibForDotNet.dll CSharpAutomation.cs
