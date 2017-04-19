function disp(m)

if numel(m) ~= 0
    n = ndims(m);
    
    if n < 3
        text = display_2d(m);
    else
        dims = size(m);
        
        text = '';
        for i=1:prod(dims(3:end))
            text = cat(2,text,display_name(subscripts(dims(3:end),i)),display_2d(m(:,:,i)));
        end
    end
    disp(text)
end


% Embedded function. Display the given name.
function [r] = display_name(index)

if ~isempty(index)
    name = ['(:,:' sprintf(',%d',index) ')'];

    if isequal(get(0,'FormatSpacing'),'compact')
        r = sprintf('%s =\n',name);
    else
        r = sprintf('\n%s =\n\n',name);
    end
else
    r = '';
end

% Embedded function. Display function for 2D arrays.
function [r] = display_2d(m)

str = '';
for c=1:size(   m,2)
    column = '';
    for r=1:size(m,1)
        column = char(column,sprintf('     %s',char(m(r,c))));
    end
    str = cat(2,str,column);
end

r = [str(2:end,:) repmat(sprintf('\n'),[size(str,1)-1 1])]';
r = r(:)';


% Embedded function. Returns subscripts from linear index.
function [r] = subscripts(dims,index)

r = zeros(size(dims));
k = [1 cumprod(dims(1:end-1))];
for i=length(dims):-1:1,
    vi = rem(index-1,k(i)) + 1;         
    vj = (index-vi)/k(i) + 1; 
    r(i) = vj; 
    index = vi;     
end