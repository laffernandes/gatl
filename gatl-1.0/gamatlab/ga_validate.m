function ga_validate(model,varargin)

% Check input arguments.
if (nargin ~= 2) && (nargin ~= 3)
    error('GAToolbox:InputArgumentsCheck','Wrong number of input arguments.')
end

model = char(model);
p = uint32(varargin{1});
if nargin == 3
    q = uint32(varargin{2});
else
    q = uint32(0);
end
n = p + q;

% Set active model.
ga_active_model(model,varargin{:})

% Sets a random seed.
rand('twister',sum(100*clock))

% Create a random scalar value.
scalar = multivector(randn);

% Create some random blades.
blade_v = multivector(ones(n,1));
if strcmp(model,'homogeneous') || strcmp(model,'conformal') || strcmp(model,'conformal_voronoi')
    blade_p = multivector(ones(n,1));
else
    blade_p = [];
end

for grade=1:n
    aux = num2cell(randn(grade,n),1);
    v = vector(aux{:});
    
    for j=1:grade
        blade_v(grade) = op(blade_v(grade),v(j));
    end
    
    if strcmp(model,'homogeneous') || strcmp(model,'conformal') || strcmp(model,'conformal_voronoi')
        aux = num2cell(randn(grade,n),1);
        p = point(aux{:});

        for j=1:grade
            blade_p(grade) = op(blade_p(grade),p(j));
        end
    end
end

blade = [0;scalar;blade_v;blade_p;randn*I];

switch model
    case 'homogeneous'
        blade = [blade;randn*e0];
    case {'conformal','conformal_voronoi'}
        blade = [blade;randn*no;randn*ni];
end

% Create some random versors.
versor = multivector(ones(0,1));

% Put all the multivectors together and set some useful multivectors.
m = [blade;versor];

aux = num2cell(randn(1,n),1);
v = vector(aux{:});

m3 = lcont(v,I);

try
    % Validate unary operations.
    disp(sprintf('\nValidate unary operations:\n'))
    validate_unary(m)

    % Validate binary operations.
    disp(sprintf('\nValidate binary operations:\n'))
    index = 1:numel(m);
    for i=1:numel(m)
        validate_binary(m(i),m(index ~= i),m3,v)
    end
catch err
    rethrow(err)
end
disp(' ')


% Embedded function. Validates unary operations.
function validate_unary(m)

zero = multivector(0);
one = multivector(1);

non_zero_m = m(m ~= zero);

invertible_m = m(is_invertible(m));

unit_em_invertible_m = unit_em(invertible_m);
unit_invertible_m = unit(invertible_m);

has_grade_0 = has_grade(0,m);
m_with_scalar = m(has_grade_0);
m_without_scalar = m(~has_grade_0);
scalar_m_with_scalar = take_grade(0,m_with_scalar);

log_test( (+m) == m, 'unary plus' )

log_test( (-m) == gp(m,-one), 'negation' )

log_test( is_zero(m) == (m == zero), 'zero multivector test' )

log_test( is_scalar(m) == (take_grade(0,m) == m), 'scalar value test' )

log_test( gp(invertible_m,inverse(invertible_m)) == one, 'inverse' )

log_test( m == undual(dual(m)), 'dualization and undualization' )

log_test( norm_em(unit_em_invertible_m) == one, 'unit under Euclidean norm and Euclidean norm' )
log_test( norm2_em(unit_em_invertible_m) == one, 'squared Euclidean norm' )

log_test( abs(norm(unit_invertible_m)) == one, 'unit under reverse norm and reverse norm' )
log_test( abs(norm2(unit_invertible_m)) == one, 'squared reverse norm' )

log_test( scp(m,zero) == zero, 'scalar product with zero at right' )
log_test( scp(zero,m) == zero, 'scalar product with zero at left' )

log_test( gp(m,zero) == zero, 'geometric product with zero at right' )
log_test( gp(zero,m) == zero, 'geometric product with zero at left' )

log_test( (m+zero) == m, 'addition with zero at right' )
log_test( (zero+m) == m, 'addition with zero at left' )

log_test( (m-zero) == m, 'subtraction with zero at right' )
log_test( (zero-m) == -m, 'subtraction with zero at left' )

log_test( igp(zero,invertible_m) == zero, 'inverse geometric product with zero at left' )

log_test( lcont(m,zero) == zero, 'left contraction with zero at right' )
log_test( lcont(zero,m) == zero, 'left contraction with zero at left' )

log_test( rcont(m,zero) == zero, 'right contraction with zero at right' )
log_test( rcont(zero,m) == zero, 'right contraction with zero at left' )

log_test( op(m,zero) == zero, 'outer product with zero at right' )
log_test( op(zero,m) == zero, 'outer product with zero at left' )

log_test( dot(m,zero) == zero, 'dot product with zero at right' )
log_test( dot(zero,m) == zero, 'dot product with zero at left' )

log_test( hip(m,zero) == zero, 'Hestenes'' inner product with zero at right' )
log_test( hip(zero,m) == zero, 'Hestenes'' inner product with zero at left' )

log_test( scp(m_with_scalar,one) == scalar_m_with_scalar, 'scalar product with one at right' )
log_test( scp(m_without_scalar,one) == zero, 'scalar product with one at right' )
log_test( scp(one,m_with_scalar) == scalar_m_with_scalar, 'scalar product with one at left' )
log_test( scp(one,m_without_scalar) == zero, 'scalar product with one at left' )

log_test( gp(non_zero_m,one) == non_zero_m, 'geometric product with one at right' )
log_test( gp(one,non_zero_m) == non_zero_m, 'geometric product with one at left' )

log_test( igp(m,one) == m, 'inverse geometric product with one at right' )

log_test( lcont(m_with_scalar,one) == scalar_m_with_scalar, 'left contraction with one at right' )
log_test( lcont(m_without_scalar,one) == zero, 'left contraction with one at right' )
log_test( lcont(one,m) == m, 'left contraction with one at left' )

log_test( rcont(m,one) == m, 'right contraction with one at right' )
log_test( rcont(one,m_with_scalar) == scalar_m_with_scalar, 'right contraction with one at left' )
log_test( rcont(one,m_without_scalar) == zero, 'right contraction with one at left' )

log_test( op(m,one) == m, 'outer product with one at right' )
log_test( op(one,m) == m, 'outer product with one at left' )

log_test( dot(m,one) == m, 'dot product with one at right' )
log_test( dot(one,m) == m, 'dot product with one at left' )

log_test( hip(m,one) == zero, 'Hestenes'' inner product with one at right' )
log_test( hip(one,m) == zero, 'Hestenes'' inner product with one at left' )


% Embedded function. Validates binary operations.
function validate_binary(m1,m2,m3,v)

zero = multivector(0);

non_zero_m1 = m1(m1 ~= zero);
non_zero_m2 = m2(m2 ~= zero);

grade_homogeneous_m1 = non_zero_m1(is_grade_homogeneous(non_zero_m1));
grade_homogeneous_m2 = non_zero_m2(is_grade_homogeneous(non_zero_m2));

intertible_m1 = m1(is_invertible(m1));
intertible_m2 = m2(is_invertible(m2));

vector1 = intertible_m1(grade(intertible_m1) == 1);
vector2 = intertible_m2(grade(intertible_m2) == 1);

log_test( (m1+m2) == (m2+m1), 'addition commutativity' );

log_test( (m1+(m2+m3)) == ((m1+m2)+m3), 'addition associativity' );

log_test( (m1-m2) == (-(m2-m1)), 'subtraction' );

log_test( gp((m1+m2),m3) == (gp(m1,m3)+gp(m2,m3)), 'geometric product distributivity over the sum' );

log_test( gp(gp(m1,m2),m3) == gp(m1,gp(m2,m3)), 'geometric product associativity' );

log_test( lcont(v,op(m1,m2)) == (op(lcont(v,m1),m2)+op(grade_involution(m1),lcont(v,m2))), 'left contraction, outer product and grade involution' );

log_test( lcont(op(m1,m2),m3) == lcont(m1,lcont(m2,m3)), 'left contraction and outer product' );

log_test( scp(m3,lcont(m1,m2)) == scp(op(m3,m1),m2), 'left contraction, outer product and scalar product' );

log_test( scp(rcont(m2,m1),m3) == scp(m2,op(m1,m3)), 'right contraction, outer product and scalar product' );

log_test( scp(m1,m2) == take_grade(0,gp(m1,m2)), 'scalar product' );

if ~isempty(grade_homogeneous_m1) && ~isempty(grade_homogeneous_m2)
    log_test( op(grade_homogeneous_m1,grade_homogeneous_m2) == gp((-1).^(grade(grade_homogeneous_m1).*grade(grade_homogeneous_m2)),op(grade_homogeneous_m2,grade_homogeneous_m1)), 'outer product for homogeneous grade' );
end

log_test( scp(m1,m2) == scp(m2,m1), 'scalar product of homogeneous grade multivectors' );

if ~isempty(vector1)
    log_test( gp(igp(m2,vector1),vector1) == m2, 'inverse geometric product' );

    log_test( gp(vector1,m2) == (lcont(vector1,m2)+op(vector1,m2)), 'geometric product, left contraction and outer product with one vector' );

    if ~isempty(vector2)
        log_test( lcont(vector1,vector2) == gp(0.5,(gp(vector1,vector2)+gp(vector2,vector1))), 'left contraction and geometric product with vectors' );

        log_test( all(lcont(vector1,vector2) == rcont(vector1,vector2)) && all(lcont(vector1,vector2) == scp(vector1,vector2)), 'left contraction, right contraction and scalar product for vectors' );
    end
end


% Embedded function. Display the result of a test into the command window.
function log_test(test_result,test_name)

if all(test_result)
    disp(sprintf('\tValidating %s... ok',test_name))
else
    disp(sprintf('\tValidating %s... error',test_name))
    error('GAToolbox:CompilerError','Houston, we have a problem.')
end