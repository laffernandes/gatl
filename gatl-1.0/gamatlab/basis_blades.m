function [r] = basis_blades(index)

e = basis_vectors;
n = numel(e);

r = reverse(prod_em(double(dec2bin(0:2^n-1)=='1').*repmat(e(end:-1:1)',2^n,1)+double(dec2bin(0:2^n-1)~='1'),2));
if nargin == 1
    r = r(index);
end