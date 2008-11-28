#pragma once

class LudoVector;
class LudoUtilities
{
public:
    static int StringToInt(std::wstring s, int minValue = 0, int maxValue = 0, int defaultValue = 0);
    static bool AreStringsEqual(const wchar_t *s1, const wchar_t *s2, bool ignoreCase = true);
    static void BSpline(int numControlPoints, int polynomialDegree, LudoVector *control, LudoVector *output, int numOutput);

private:
    static void ComputePoints(int *tempArray, int numControlPoints, int polynomialDegree, float interval, LudoVector *control,  LudoVector *output);
    static float Blend(int index, int polynomialDegree, int *tempArray, float interval);
    static void ComputeIntervals(int *tempArray, int numControlPoints, int polynomialDegree);
};
