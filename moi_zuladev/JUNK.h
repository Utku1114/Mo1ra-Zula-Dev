#define J() UsefulFuntion(24567, 3324, 4537, 2345);
inline int UsefulFuntion(int x, int y, int z, int r)
{
	for (int i = 2; i < 8; i++)
	{
		z += 456;
		r -= 55;
		x++;
		y--;

	}
	for (int i = 0; i < 2; i++)
	{
		x++;
		y += 234;
		z -= 23;
		r += 634;
	}
	return x + z + r + y;
}