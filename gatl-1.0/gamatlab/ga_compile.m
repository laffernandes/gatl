function ga_compile(compiler,model,varargin)

% Check input arguments.
if (nargin ~= 3) && (nargin ~= 4)
    error('GAToolbox:InputArgumentsCheck','Wrong number of input arguments.')
end

compiler = lower(char(compiler));
if ~strcmp(compiler,'gcc') && ~strcmp(compiler,'vc') && ~strcmp(compiler,'default')
    error('GAToolbox:InputArgumentsCheck','Unknown compiler name ''%s''.\nPlease, use\n\t''gcc'' for GCC,\n\t''vc'' for Visual C++ or\n\t''default'' for default MEX options.\nSee <a href="matlab:doc mex">mex -setup</a> help page for further reference on default MEX options.',compiler)
end

model = lower(char(model));
p = uint32(varargin{1});
if nargin == 4
    q = uint32(varargin{2});
else
    q = uint32(0);
end
base_space_dims = p + q;

% Get specialized model name.
model_name = ga_active_model(model,varargin{:});

% Get package's base path, include path, etc.
base_path = fileparts([mfilename('fullpath') '.m']);

source_path = [base_path filesep 'source'];

bmathlib_path = [base_path filesep '..' filesep 'bmathlib' filesep 'include'];
btoolslib_path = [base_path filesep '..' filesep 'btoolslib' filesep 'include'];
btriglib_path = [base_path filesep '..' filesep 'btriglib' filesep 'include'];
galib_path = [base_path filesep '..' filesep 'galib' filesep 'include'];
lalib_path = [base_path filesep '..' filesep 'lalib' filesep 'include'];
smathlib_path = [base_path filesep '..' filesep 'smathlib' filesep 'include'];
stoolslib_path = [base_path filesep '..' filesep 'stoolslib' filesep 'include'];

if ispc
    switch compiler
        case 'gcc', mex_options_file = ['-f ''' source_path filesep 'mexopts_gcc.bat'''];
        case 'vc', mex_options_file = ['-f ''' source_path filesep 'mexopts_vc.bat'''];
        case 'default', mex_options_file = '';
    end
end

persistent gcc_path
persistent msvs_path

% Display welcome message.
disp(' ')
disp('------------------------------------------------------------------')
disp('               GEOMETRIC ALGEBRA TOOLBOX FOR MATLAB')
disp('------------------------------------------------------------------')
disp(' ')
disp(sprintf('\tCopyright (C) 2007 Leandro Augusto Frata Fernandes'))
disp(sprintf('\tauthor    : Fernandes, Leandro A. F.'))
disp(sprintf('\te-mail    : laffernandes@gmail.com'))
disp(sprintf('\thome page : http://www.inf.ufrgs.br/~laffernandes'))
disp(sprintf('\tversion   : Alpha 3.141592'))
disp(' ')
disp(' ')
disp('Compilation properties')
disp('----------------------')
disp(' ')
disp(sprintf('\tModel Name            : ''%s''',model))
disp(sprintf('\tBase Space Dimensions : %d',base_space_dims))
if strcmp(model,'clifford')
    disp(sprintf('\b (p=%d,q=%d)',p,q))
end
disp(sprintf('\tInternal Name         : ''%s''',model_name))

step = 1;
steps_count = 2;
if ispc 
    if strcmp(compiler,'gcc')
        disp(' ')
        disp(sprintf('\tGCC Directory         : '))
        if isempty(gcc_path)
            gcc_path = uigetdir(['C:' filesep 'MinGW'],['Select GCC directory (e.g., ''C:' filesep 'MinGW'')']);

            if gcc_path == 0
                disp(sprintf('\bunknown'))
                disp(' ')
                disp(' ')
                disp('Compilation process canceled by the user.')
                disp(' ')

                gcc_path = [];
                return
            end
        end
        setenv('GA_GCC_PATH',gcc_path)
        disp(sprintf('\b''%s''',gcc_path))

        steps_count = 4;
    elseif strcmp(compiler,'vc')
        disp(' ')
        disp(sprintf('\tMicrosoft Visual Studio Directory: '))
        if isempty(msvs_path)
            msvs_path = uigetdir(['C:' filesep 'Program Files' filesep 'Microsoft Visual Studio 9.0'],['Select Microsoft Visual Studio directory (e.g., ''C:' filesep 'Program Files' filesep 'Microsoft Visual Studio 9.0'')']);

            if msvs_path == 0
                disp(sprintf('\bunknown'))
                disp(' ')
                disp(' ')
                disp('Compilation process canceled by the user.')
                disp(' ')

                msvs_path = [];
                return
            end
        end
        setenv('GA_MSVS_PATH',msvs_path)
        disp(sprintf('\b''%s''',msvs_path))
    end
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Compile MATLAB libs.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if ispc && strcmp(compiler,'gcc')
    disp(' ')
    disp(' ')
    disp(sprintf('Step %d of %d: Compile MATLAB libs',step,steps_count))
    disp('--------------------------------')
    disp(' ')

    matlablib_name = {'libmx','libmex'};

    for i=1:length(matlablib_name)
        disp(sprintf('\tCompiling ''%s''... ',char(matlablib_name(i))))
        system([gcc_path filesep 'bin' filesep 'dlltool --input-def "' source_path filesep char(matlablib_name(i)) '.def" --output-lib "' base_path filesep 'ga_' char(matlablib_name(i)) '.lib"']);
        disp(sprintf('\bdone'))
    end
    step = step + 1;
end

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Compile MEX-files.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp(' ')
disp(' ')
disp(sprintf('Step %d of %d: Compile MEX-files',step,steps_count))
disp('------------------------------')
disp(' ')

compilation_list = cell(0,2);

% Embedded function. Adds a operation to the compilation list.
function push_operation(source_file,operation,varargin)
    arg = [
        '-DGA_HIGHEST_ASSERTION_LEVEL ' ...
        '-DUSING_' upper(model) '_MODEL ' ...
        '-DBASE_SPACE_DIMS#' int2str(base_space_dims) ' ' ...
        '-DP_VECTORS#' int2str(p) ' ' ...
        '-DQ_VECTORS#' int2str(q) ' ' ...
        mex_options_file ' ' ...
        '-O ' ...
        '-I''' source_path ''' ' ...
        '-I''' bmathlib_path ''' ' ...
        '-I''' btoolslib_path ''' ' ...
        '-I''' btriglib_path ''' ' ...
        '-I''' galib_path ''' ' ...
        '-I''' lalib_path ''' ' ...
        '-I''' smathlib_path ''' ' ...
        '-I''' stoolslib_path ''' ' ...
        '-outdir ''' base_path ''' ' ...
        '-output ''' model_name '_' operation ''' ' ...
        '''' source_path filesep source_file ''''];
    
    if isempty(varargin)
        compilation_list(end+1,:) = {operation,['mex ' arg]};
    else
        compilation_list(end+1,:) = {operation,['mex ' sprintf('-D%s#%s ',varargin{:}) arg]};
    end
end

% Setup "unary_test_tol.cpp" operations.
push_operation('unary_test_tol.cpp','has_even_grade_only','OPERATION','ga::has_even_grade_only');
push_operation('unary_test_tol.cpp','has_odd_grade_only','OPERATION','ga::has_odd_grade_only');
push_operation('unary_test_tol.cpp','is_blade','OPERATION','ga::is_blade');
push_operation('unary_test_tol.cpp','is_grade_homogeneous','OPERATION','ga::is_grade_homogeneous');
push_operation('unary_test_tol.cpp','is_invertible','OPERATION','ga::is_invertible');
push_operation('unary_test_tol.cpp','is_invertible_em','OPERATION','ga::is_invertible_em');
push_operation('unary_test_tol.cpp','is_invertible_mv','OPERATION','ga::is_invertible_mv');
push_operation('unary_test_tol.cpp','is_invertible_mv_em','OPERATION','ga::is_invertible_mv_em');
push_operation('unary_test_tol.cpp','is_null','OPERATION','ga::is_null');
push_operation('unary_test_tol.cpp','is_rotor','OPERATION','ga::is_rotor');
push_operation('unary_test_tol.cpp','is_rotor_em','OPERATION','ga::is_rotor_em');
push_operation('unary_test_tol.cpp','is_scalar','OPERATION','ga::is_scalar');
push_operation('unary_test_tol.cpp','is_pseudoscalar','OPERATION','ga::is_pseudoscalar');
push_operation('unary_test_tol.cpp','is_unit','OPERATION','ga::is_unit');
push_operation('unary_test_tol.cpp','is_unit_em','OPERATION','ga::is_unit_em');
push_operation('unary_test_tol.cpp','is_versor','OPERATION','ga::is_versor');
push_operation('unary_test_tol.cpp','is_versor_em','OPERATION','ga::is_versor_em');
push_operation('unary_test_tol.cpp','is_zero','OPERATION','ga::is_zero');

switch model
    case 'homogeneous'
        push_operation('unary_test_tol.cpp','is_direction','OPERATION','ga::homogeneous::is_direction');
        push_operation('unary_test_tol.cpp','is_flat','OPERATION','ga::homogeneous::is_flat');
        push_operation('unary_test_tol.cpp','is_improper_flat','OPERATION','ga::homogeneous::is_improper_flat');
        push_operation('unary_test_tol.cpp','is_proper_flat','OPERATION','ga::homogeneous::is_proper_flat');
    case {'conformal','conformal_voronoi'}
        push_operation('unary_test_tol.cpp','is_direction','OPERATION','ga::conformal::is_direction');
        push_operation('unary_test_tol.cpp','is_dual_direction','OPERATION','ga::conformal::is_dual_direction');
        push_operation('unary_test_tol.cpp','is_dual_flat','OPERATION','ga::conformal::is_dual_flat');
        push_operation('unary_test_tol.cpp','is_dual_round','OPERATION','ga::conformal::is_dual_round');
        push_operation('unary_test_tol.cpp','is_dual_tangent','OPERATION','ga::conformal::is_dual_tangent');
        push_operation('unary_test_tol.cpp','is_flat','OPERATION','ga::conformal::is_flat');
        push_operation('unary_test_tol.cpp','is_round','OPERATION','ga::conformal::is_round');
        push_operation('unary_test_tol.cpp','is_tangent','OPERATION','ga::conformal::is_tangent');
end

% Setup "unary_operation.cpp" operations.
push_operation('unary_operation.cpp','clifford_conjugation','OPERATION','ga::clifford_conjugation');
push_operation('unary_operation.cpp','dual_unary','OPERATION','ga::dual');
push_operation('unary_operation.cpp','dual_em_unary','OPERATION','ga::dual_em');
push_operation('unary_operation.cpp','grade_involution','OPERATION','ga::grade_involution');
push_operation('unary_operation.cpp','norm2','OPERATION','ga::norm2');
push_operation('unary_operation.cpp','norm2_em','OPERATION','ga::norm2_em');
push_operation('unary_operation.cpp','reverse','OPERATION','ga::reverse');
push_operation('unary_operation.cpp','undual_unary','OPERATION','ga::undual');
push_operation('unary_operation.cpp','undual_em_unary','OPERATION','ga::undual_em');
push_operation('unary_operation.cpp','uminus','OPERATION','ga::uminus');
push_operation('unary_operation.cpp','uplus','OPERATION','ga::uplus');

% Setup "unary_operation_tol.cpp" operations.
push_operation('unary_operation_tol.cpp','abs','OPERATION','ga::abs');
push_operation('unary_operation_tol.cpp','cleanup','OPERATION','ga::cleanup');
push_operation('unary_operation_tol.cpp','exp','OPERATION','ga::exp');
push_operation('unary_operation_tol.cpp','exp_em','OPERATION','ga::exp_em');
push_operation('unary_operation_tol.cpp','inverse','OPERATION','ga::inverse');
push_operation('unary_operation_tol.cpp','inverse_em','OPERATION','ga::inverse_em');
push_operation('unary_operation_tol.cpp','inverse_mv','OPERATION','ga::inverse_mv');
push_operation('unary_operation_tol.cpp','inverse_mv_em','OPERATION','ga::inverse_mv_em');
push_operation('unary_operation_tol.cpp','norm','OPERATION','ga::norm');
push_operation('unary_operation_tol.cpp','norm_em','OPERATION','ga::norm_em');
push_operation('unary_operation_tol.cpp','sqrt','OPERATION','ga::sqrt');
push_operation('unary_operation_tol.cpp','take_largest_grade','OPERATION','ga::take_largest_grade');
push_operation('unary_operation_tol.cpp','unit','OPERATION','ga::unit');
push_operation('unary_operation_tol.cpp','unit_em','OPERATION','ga::unit_em');

switch model
    case'homogeneous'
        push_operation('unary_operation_tol.cpp','flat_direction','OPERATION','ga::homogeneous::flat_direction');
        push_operation('unary_operation_tol.cpp','flat_moment','OPERATION','ga::homogeneous::flat_moment');
        push_operation('unary_operation_tol.cpp','flat_support_vector','OPERATION','ga::homogeneous::flat_support_vector');
        push_operation('unary_operation_tol.cpp','flat_unit_support_point','OPERATION','ga::homogeneous::flat_unit_support_point');
    case {'conformal','conformal_voronoi'}
        push_operation('unary_operation_tol.cpp','flat_direction','OPERATION','ga::conformal::flat_direction');
        push_operation('unary_operation_tol.cpp','flat_location','OPERATION','ga::conformal::flat_location');
        push_operation('unary_operation_tol.cpp','round_direction','OPERATION','ga::conformal::round_direction');
        push_operation('unary_operation_tol.cpp','round_location','OPERATION','ga::conformal::round_location');
        push_operation('unary_operation_tol.cpp','round_size2','OPERATION','ga::conformal::round_size2');
        push_operation('unary_operation_tol.cpp','tangent_direction','OPERATION','ga::conformal::tangent_direction');
        push_operation('unary_operation_tol.cpp','tangent_location','OPERATION','ga::conformal::tangent_location');
        push_operation('unary_operation_tol.cpp','tangent_size2','OPERATION','ga::conformal::tangent_size2');
end

% Setup multivector cast to matrices.
push_operation('multivector_matrix.cpp','multivector_matrix','OPERATION','ga::multivector_matrix');

% Setup product cast to matrices.
push_operation('unary_operation_matrix.cpp','clifford_conjugation_matrix','OPERATION','ga::clifford_conjugation_matrix');
push_operation('unary_operation_matrix.cpp','grade_involution_matrix','OPERATION','ga::grade_involution_matrix');
push_operation('unary_operation_matrix.cpp','reverse_matrix','OPERATION','ga::reverse_matrix');

push_operation('binary_operation_matrix.cpp','dot_matrixl','OPERATION','ga::dot_matrix','MULTIPLICATION_TYPE','ga::left_multiplication');
push_operation('binary_operation_matrix.cpp','dot_matrixr','OPERATION','ga::dot_matrix','MULTIPLICATION_TYPE','ga::right_multiplication');
push_operation('binary_operation_matrix.cpp','dot_matrixl_em','OPERATION','ga::dot_matrix_em','MULTIPLICATION_TYPE','ga::left_multiplication');
push_operation('binary_operation_matrix.cpp','dot_matrixr_em','OPERATION','ga::dot_matrix_em','MULTIPLICATION_TYPE','ga::right_multiplication');
push_operation('binary_operation_matrix.cpp','gp_matrixl','OPERATION','ga::gp_matrix','MULTIPLICATION_TYPE','ga::left_multiplication');
push_operation('binary_operation_matrix.cpp','gp_matrixr','OPERATION','ga::gp_matrix','MULTIPLICATION_TYPE','ga::right_multiplication');
push_operation('binary_operation_matrix.cpp','gp_matrixl_em','OPERATION','ga::gp_matrix_em','MULTIPLICATION_TYPE','ga::left_multiplication');
push_operation('binary_operation_matrix.cpp','gp_matrixr_em','OPERATION','ga::gp_matrix_em','MULTIPLICATION_TYPE','ga::right_multiplication');
push_operation('binary_operation_matrix.cpp','hip_matrixl','OPERATION','ga::hip_matrix','MULTIPLICATION_TYPE','ga::left_multiplication');
push_operation('binary_operation_matrix.cpp','hip_matrixr','OPERATION','ga::hip_matrix','MULTIPLICATION_TYPE','ga::right_multiplication');
push_operation('binary_operation_matrix.cpp','hip_matrixl_em','OPERATION','ga::hip_matrix_em','MULTIPLICATION_TYPE','ga::left_multiplication');
push_operation('binary_operation_matrix.cpp','hip_matrixr_em','OPERATION','ga::hip_matrix_em','MULTIPLICATION_TYPE','ga::right_multiplication');
push_operation('binary_operation_matrix.cpp','lcont_matrixl','OPERATION','ga::lcont_matrix','MULTIPLICATION_TYPE','ga::left_multiplication');
push_operation('binary_operation_matrix.cpp','lcont_matrixr','OPERATION','ga::lcont_matrix','MULTIPLICATION_TYPE','ga::right_multiplication');
push_operation('binary_operation_matrix.cpp','lcont_matrixl_em','OPERATION','ga::lcont_matrix_em','MULTIPLICATION_TYPE','ga::left_multiplication');
push_operation('binary_operation_matrix.cpp','lcont_matrixr_em','OPERATION','ga::lcont_matrix_em','MULTIPLICATION_TYPE','ga::right_multiplication');
push_operation('binary_operation_matrix.cpp','op_matrixl','OPERATION','ga::op_matrix','MULTIPLICATION_TYPE','ga::left_multiplication');
push_operation('binary_operation_matrix.cpp','op_matrixr','OPERATION','ga::op_matrix','MULTIPLICATION_TYPE','ga::right_multiplication');
push_operation('binary_operation_matrix.cpp','rcont_matrixl','OPERATION','ga::rcont_matrix','MULTIPLICATION_TYPE','ga::left_multiplication');
push_operation('binary_operation_matrix.cpp','rcont_matrixr','OPERATION','ga::rcont_matrix','MULTIPLICATION_TYPE','ga::right_multiplication');
push_operation('binary_operation_matrix.cpp','rcont_matrixl_em','OPERATION','ga::rcont_matrix_em','MULTIPLICATION_TYPE','ga::left_multiplication');
push_operation('binary_operation_matrix.cpp','rcont_matrixr_em','OPERATION','ga::rcont_matrix_em','MULTIPLICATION_TYPE','ga::right_multiplication');
push_operation('binary_operation_matrix.cpp','scp_matrixl','OPERATION','ga::scp_matrix','MULTIPLICATION_TYPE','ga::left_multiplication');
push_operation('binary_operation_matrix.cpp','scp_matrixr','OPERATION','ga::scp_matrix','MULTIPLICATION_TYPE','ga::right_multiplication');
push_operation('binary_operation_matrix.cpp','scp_matrixl_em','OPERATION','ga::scp_matrix_em','MULTIPLICATION_TYPE','ga::left_multiplication');
push_operation('binary_operation_matrix.cpp','scp_matrixr_em','OPERATION','ga::scp_matrix_em','MULTIPLICATION_TYPE','ga::right_multiplication');

% Setup product cast to tensors.
push_operation('unary_operation_tensor.cpp','clifford_conjugation_tensor','OPERATION','ga::clifford_conjugation_tensor');
push_operation('unary_operation_tensor.cpp','grade_involution_tensor','OPERATION','ga::grade_involution_tensor');
push_operation('unary_operation_tensor.cpp','reverse_tensor','OPERATION','ga::reverse_tensor');

push_operation('binary_operation_tensor.cpp','dot_tensor','OPERATION','ga::dot_tensor');
push_operation('binary_operation_tensor.cpp','dot_tensor_em','OPERATION','ga::dot_tensor_em');
push_operation('binary_operation_tensor.cpp','gp_tensor','OPERATION','ga::gp_tensor');
push_operation('binary_operation_tensor.cpp','gp_tensor_em','OPERATION','ga::gp_tensor_em');
push_operation('binary_operation_tensor.cpp','hip_tensor','OPERATION','ga::hip_tensor');
push_operation('binary_operation_tensor.cpp','hip_tensor_em','OPERATION','ga::hip_tensor_em');
push_operation('binary_operation_tensor.cpp','lcont_tensor','OPERATION','ga::lcont_tensor');
push_operation('binary_operation_tensor.cpp','lcont_tensor_em','OPERATION','ga::lcont_tensor_em');
push_operation('binary_operation_tensor.cpp','op_tensor','OPERATION','ga::op_tensor');
push_operation('binary_operation_tensor.cpp','rcont_tensor','OPERATION','ga::rcont_tensor');
push_operation('binary_operation_tensor.cpp','rcont_tensor_em','OPERATION','ga::rcont_tensor_em');
push_operation('binary_operation_tensor.cpp','scp_tensor','OPERATION','ga::scp_tensor');
push_operation('binary_operation_tensor.cpp','scp_tensor_em','OPERATION','ga::scp_tensor_em');

% Setup "binary_test_tol.cpp" operations.
push_operation('binary_test_tol.cpp','equal','OPERATION','ga::equal');

% Setup "binary_operation_tol.cpp" operations.
push_operation('binary_operation.cpp','cmp','OPERATION','ga::cmp');
push_operation('binary_operation.cpp','cmp_em','OPERATION','ga::cmp_em');
push_operation('binary_operation.cpp','dot','OPERATION','ga::dot');
push_operation('binary_operation.cpp','dot_em','OPERATION','ga::dot_em');
push_operation('binary_operation.cpp','gp','OPERATION','ga::gp');
push_operation('binary_operation.cpp','gp_em','OPERATION','ga::gp_em');
push_operation('binary_operation.cpp','hip','OPERATION','ga::hip');
push_operation('binary_operation.cpp','hip_em','OPERATION','ga::hip_em');
push_operation('binary_operation.cpp','lcont','OPERATION','ga::lcont');
push_operation('binary_operation.cpp','lcont_em','OPERATION','ga::lcont_em');
push_operation('binary_operation.cpp','minus','OPERATION','ga::minus');
push_operation('binary_operation.cpp','op','OPERATION','ga::op');
push_operation('binary_operation.cpp','plus','OPERATION','ga::plus');
push_operation('binary_operation.cpp','rcont','OPERATION','ga::rcont');
push_operation('binary_operation.cpp','rcont_em','OPERATION','ga::rcont_em');
push_operation('binary_operation.cpp','scp','OPERATION','ga::scp');
push_operation('binary_operation.cpp','scp_em','OPERATION','ga::scp_em');
push_operation('binary_operation.cpp','undual_binary','OPERATION','ga::undual');
push_operation('binary_operation.cpp','undual_em_binary','OPERATION','ga::undual_em');

% Setup "binary_operation_tol.cpp" operations.
push_operation('binary_operation_tol.cpp','apply_even_versor','OPERATION','ga::apply_even_versor');
push_operation('binary_operation_tol.cpp','apply_even_versor_em','OPERATION','ga::apply_even_versor_em');
push_operation('binary_operation_tol.cpp','apply_odd_versor','OPERATION','ga::apply_odd_versor');
push_operation('binary_operation_tol.cpp','apply_odd_versor_em','OPERATION','ga::apply_odd_versor_em');
push_operation('binary_operation_tol.cpp','delta','OPERATION','ga::delta');
push_operation('binary_operation_tol.cpp','delta_em','OPERATION','ga::delta_em');
push_operation('binary_operation_tol.cpp','dual_binary','OPERATION','ga::dual');
push_operation('binary_operation_tol.cpp','dual_em_binary','OPERATION','ga::dual_em');
push_operation('binary_operation_tol.cpp','fast_join','OPERATION','ga::fast_join');
push_operation('binary_operation_tol.cpp','fast_meet','OPERATION','ga::fast_meet');
push_operation('binary_operation_tol.cpp','igp','OPERATION','ga::igp');
push_operation('binary_operation_tol.cpp','igp_em','OPERATION','ga::igp_em');
push_operation('binary_operation_tol.cpp','join','OPERATION','ga::join');
push_operation('binary_operation_tol.cpp','meet','OPERATION','ga::meet');

switch model
    case 'euclidean'
        push_operation('binary_operation_tol.cpp','project','OPERATION','ga::euclidean::project');
        push_operation('binary_operation_tol.cpp','reject','OPERATION','ga::euclidean::reject');
    case 'homogeneous'
        push_operation('binary_operation_tol.cpp','translate','OPERATION','ga::homogeneous::translate');
end

% Setup "builder.cpp" operations.
switch model
    case 'clifford'
        push_operation('builder.cpp','vector','OPERATION','ga::clifford::vector');
    case 'euclidean'
        push_operation('builder.cpp','vector','OPERATION','ga::euclidean::vector');
    case 'homogeneous'
        push_operation('builder.cpp','point','OPERATION','ga::homogeneous::point');
        push_operation('builder.cpp','vector','OPERATION','ga::homogeneous::vector');
    case {'conformal','conformal_voronoi'}
        push_operation('builder.cpp','point','OPERATION','ga::conformal::point');
        push_operation('builder.cpp','vector','OPERATION','ga::conformal::vector');
end

% Setup other operations.
push_operation('factorize_em.cpp','factorize_em');
push_operation('fast_factorize_em.cpp','fast_factorize_em');
push_operation('grade.cpp','grade');
push_operation('has_grade.cpp','has_grade');
push_operation('interpret.cpp','interpret');
push_operation('metric.cpp','metric');
push_operation('sign.cpp','sign');
push_operation('take_grade.cpp','take_grade');
push_operation('consts.cpp','consts'); % This method is for internal use only. So, it does not need a .m file.
push_operation('scalar.cpp','scalar'); % This method is for internal use only. So, it does not need a .m file.
push_operation('write.cpp','write'); % This method is for internal use only. So, it does not need a .m file.

% Sort operations by name.
compilation_list = sortrows(compilation_list);

% Compile MEX-files.
compilation_done = true(size(compilation_list,1),1);
for i=1:size(compilation_list,1)
    operation = compilation_list{i,1};
    mex_command = compilation_list{i,2};

    disp(sprintf('\tCompiling ''%s''... ',operation))

    tic
    try
        eval(mex_command);
        status = 'done';
    catch err
        compilation_done(i) = false;
        status = sprintf('\n\terror (%s)',err.identifier);
    end

    hrs_min_sec = toc/3600;
    hrs = fix(hrs_min_sec);
    min_sec = 60*(hrs_min_sec-hrs);
    min = fix(min_sec);
    sec = 60*(min_sec-min);
    
    if hrs > 0
        disp(sprintf('\b%s (%d hrs, %d min, %1.2f sec)',status,hrs,min,sec))
    elseif min > 0
        disp(sprintf('\b%s (%d min, %1.2f sec)',status,min,sec))
    else
        disp(sprintf('\b%s (%1.2f sec)',status,sec))
    end
end

step = step + 1;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Create .m function files that makes the global variables constant.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
disp(' ')
disp(' ')
disp(sprintf('Step %d of %d: Create global variables',step,steps_count))
disp('------------------------------------')
disp(' ')

global_const_script = [ ...
    'function [r] = %s()'                                                       '\n' ...
    ''                                                                          '\n' ...
    'persistent const'                                                          '\n' ...
    ''                                                                          '\n' ...
    'model_name = ga_active_model;'                                             '\n' ...
    ''                                                                          '\n' ...
    'if ~isempty(const) && strcmp(model(const),model_name)'                     '\n' ...
    '    r = const;'                                                            '\n' ...
    'else'                                                                      '\n' ...
    '    r = [];'                                                               '\n' ...
    ''                                                                          '\n' ...
    '    consts = str2func([model_name ''_consts'']);'                          '\n' ...
    '    try'                                                                   '\n' ...
    '       global_consts = consts();'                                          '\n' ...
    '    catch err'                                                             '\n' ...
    '        switch err.identifier'                                             '\n' ...
    '            case ''MATLAB:UndefinedFunction'''                             '\n' ...
    '                error(''GAToolbox:UndefinedModel'',[''Geometric algebra model '''''' model_name '''''' was not compiled.''])'	'\n' ...
    '            otherwise'                                                     '\n' ...
    '                rethrow(err);'                                             '\n' ...
    '        end'                                                               '\n' ...
    '    end'                                                                   '\n' ...
    ''                                                                          '\n' ...
    '    for i=1:length(global_consts)'                                         '\n' ...
    '        if strcmp(global_consts(i).name,''%s'')'                           '\n' ...
    '            r = multivector(global_consts(i).value);'                      '\n' ...
    '        end'                                                               '\n' ...
    '    end'                                                                   '\n' ...
    '    const = r;'                                                            '\n' ...
    ''                                                                          '\n' ...
    '    if isempty(r)'                                                         '\n' ...
    '        error(''GAToolbox:UndefinedFunction'',''The active geometric algebra model does not define this global constant value.'')' '\n' ...
    '    end'                                                                   '\n' ...
    'end'                                                                       '\n' ...
];

try
    consts = str2func([model_name '_consts']);
    global_consts = consts();

    for i=1:length(global_consts)
        disp(sprintf('\tCreating ''%s''... ',global_consts(i).name))

        filename = [base_path filesep global_consts(i).name '.m'];
        fid = fopen(filename,'w');
        fprintf(fid,global_const_script,global_consts(i).name,global_consts(i).name);
        fclose(fid);

        disp(sprintf('\bdone'))
    end
    global_consts_created = true;
catch err
	disp(sprintf('\tError (%s)! Global variables were not created.',err.identifier))
	global_consts_created = false;
end

step = step + 1;

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% Cleanup MATLAB libs.
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
if ispc && strcmp(compiler,'gcc')
    disp(' ')
    disp(' ')
    disp(sprintf('Step %d of %d: Cleanup MATLAB libs',step,steps_count))
    disp('--------------------------------')
    disp(' ')

    for i=1:length(matlablib_name)
        disp(sprintf('\tDeleting ''%s''... ',char(matlablib_name(i))))
        delete([base_path filesep 'ga_' char(matlablib_name(i)) '.lib'])
        disp(sprintf('\bdone'))
    end
end

disp(' ')
disp(' ')

if all(compilation_done) && global_consts_created
    disp('Job done!')
else
    disp('Warning! One or more steps of the compilation process failed:')
    disp(' ')
    problems_list = compilation_list(~compilation_done,1);
    for i=1:length(problems_list)
        disp(sprintf('\t''%s'' was not compiled.',problems_list{i}))
    end
    if ~global_consts_created
        disp(sprintf('\tGlobal variables were not created.'))
    end
end
disp(' ')

end