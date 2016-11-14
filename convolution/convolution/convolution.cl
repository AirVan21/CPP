__kernel void convolution(__global float* input, __global float* mask, __global float* output, int mask_width, int width)
{
	int row = get_global_id(0);
	int col = get_global_id(1);
	int HM = (mask_width - 1) / 2;

	if (row >= width || col >= width)
	{
		return;
	}

	float res = 0;
	for (int k = -HM; k <= HM; ++k)
	{
		for (int l = -HM; l <= HM; ++l)
		{
			int i = row + k;
			int j = col + l;

			bool is_valid = (i >= 0) && (j >= 0) && (i < width) && (j < width);
			float add = is_valid ? input[i * width + j] : 0.0;

			int mask_index = (k + HM) * mask_width + (l + HM);
			res += add * mask[mask_index];
		}
	}

	output[row * width + col] = res;
}