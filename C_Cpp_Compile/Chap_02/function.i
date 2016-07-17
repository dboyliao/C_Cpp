float add_and_multiply(float x, float y);

int nCompletionStatus = 0;

float add(float x, float y)
{
    return x + y;
}

float add_and_multiply(float x, float y)
{
    float z = add(x, y);
    z *= 3.0;
    return z;
}
