function [goodLocalRegions, goodSeedPoints, estDims] = lmsvd(X, opts)

%
% Multiscale SVD analysis for Linear manifolds (LMSVD)
%
% function [goodLocalRegions, goodSeedPoints, estDims] = lmsvd(X, opts)
%
% INPUT
%   X: N-by-D data matrix
%   opts: structure of the following optional parameters:
%       .seeds: seed points at which multiscale SVD analysis is performed
%       .dmax: upper bound on the plane dimensions 
%       .MinNetPts: minimum scale
%       .nScales: number of scales
%       .nPtsPerScale: number of points per scale
%       .showSpectrum: number of randomly selected seed points for which 
%           the spectrum will be shown
%       .alpha0: cutoff slope for separating noise s.v. from tangential s.v.
%
% OUTPUT
%   goodLocalRegions: a cell array of good local scales
%   goodSeedPoints: the sampled points at which the msvd analysis is performed
%   estDims: estimated intrinsic dimensions of the above local regions
%
% (c)2011 Mauro Maggioni and Guangliang Chen
% Contact: {mauro, glchen}@math.duke.edu. 
%

%% Set parameters
if nargin<1,
    error('Data set needs to be provided!')
end

[N,D] = size(X);

if nargin<2,
    opts = struct();
end;

if ~isfield(opts, 'seeds')
    opts.seeds = 1:N;
end

if ~isfield(opts, 'alpha0')
    if ~isfield(opts, 'dmax') || opts.dmax>=D
        opts.dmax = D-1; 
        opts.alpha0 = 0.2;
    else
        opts.alpha0 = 0.3/sqrt(opts.dmax);
    end
end

maxKNN = round(min(N/5, 50*opts.dmax*log(max(3,opts.dmax))));

if ~isfield(opts, 'MinNetPts')
    opts.MinNetPts = opts.dmax+2;
end

if ~isfield(opts, 'nScales')
    opts.nScales = min(50, maxKNN);
end

if ~isfield(opts, 'nPtsPerScale')
    opts.nPtsPerScale = round( maxKNN / opts.nScales );
end

if ~isfield(opts, 'plotFigs')
    opts.plotFigs = false;
end

if ~isfield(opts, 'showSpectrum')
    opts.showSpectrum = 0;
end

%%
n0 = numel(opts.seeds);
maxKNN = opts.MinNetPts + opts.nPtsPerScale*(opts.nScales-1);

% Compute the distance between the seed point and all the other points
[~, idxs, statdists] = nrsearch(X, uint32(opts.seeds), maxKNN, [], [], struct('XIsTransposed',true,'ReturnAsArrays',true));

Delta = statdists(:,opts.MinNetPts:opts.nPtsPerScale:maxKNN);

%%
Nets = cell(1,opts.nScales);
MSVD_Stats = zeros(n0, D, opts.nScales);

for j = 1:opts.nScales
    
    Nets{j}.count = opts.MinNetPts + (j-1)*opts.nPtsPerScale;
    Nets{j}.AbsInvIdxs = idxs(:, 1:Nets{j}.count);
    Nets{j}.S = zeros(n0, D);
    Nets{j}.Delta = Delta(:,j);
    
    for i = 1:n0
        net = X(Nets{j}.AbsInvIdxs(i,:),:);
        sigs = svd(net-repmat(mean(net,1), size(net,1),1));
        %sigs = svds(net-repmat(mean(net,1), size(net,1),1),opts.dmax+1);
        sigs = sigs'/sqrt(size(net,1));
        Nets{j}.S(i,1:length(sigs)) = sigs;
    end
    
    MSVD_Stats(:,:,j) = Nets{j}.S;
    
end

%%
estDims = zeros(1, n0);
GoodScales = zeros(n0,2);
for i = 1:n0,
    lS = (squeeze(MSVD_Stats(i,:,:)))'; 
    lStats = EstimateDimFromSpectra(Delta(i,:)', lS, opts.alpha0);
    estDims(i) = lStats.DimEst;
    GoodScales(i,:) = lStats.GoodScales;
end;

if opts.plotFigs
    % figure;plot(sort(estDims));axis tight; title('Estimate ptwise dimensionality');
    figure;scatter3(X(opts.seeds,1),X(opts.seeds,2),X(opts.seeds,3),20,estDims,'filled');colorbar;
    title('Pointwise Dimension Estimates', 'fontSize', 14); grid off; axis tight
end

lMaxScale = GoodScales(:,2)';
lMinScale  = GoodScales(:,1)';
lScale = lMaxScale;
   
if opts.plotFigs
    figure;scatter3(X(opts.seeds,1),X(opts.seeds,2),X(opts.seeds,3),30,lScale,'filled');colorbar;
    title('Optimal Local Scales', 'fontSize', 14); grid off; axis tight
end

goodLocalRegions = cell(1,n0);
for i = 1:n0
    goodLocalRegions{i} = idxs(i, 1:opts.MinNetPts+(lScale(i)-1)*opts.nPtsPerScale); % find(dists(i,:) <lScale(goodSeedPoints(i))^2);
end

%%
goodSeedPoints = (cellfun(@length, goodLocalRegions)>2*estDims & estDims<D);

goodLocalRegions = goodLocalRegions(goodSeedPoints);
estDims = estDims(goodSeedPoints);
goodSeedPoints = opts.seeds(goodSeedPoints);

%%
if opts.showSpectrum > 0
    
    R = zeros(1,N); R([goodLocalRegions{:}]) = 1; R = find(R>0);
    n0 = numel(goodSeedPoints);
    
    tempDelta = Delta';
    lScale  = tempDelta((0:size(tempDelta,1):size(tempDelta,1)*(size(tempDelta,2)-1)) + lScale)';
    lMinScale  = tempDelta((0:size(tempDelta,1):size(tempDelta,1)*(size(tempDelta,2)-1)) + lMinScale)';
    lMaxScale = tempDelta((0:size(tempDelta,1):size(tempDelta,1)*(size(tempDelta,2)-1)) + lMaxScale)';

    seeds = randsample(1:n0, opts.showSpectrum);
    for j = seeds
        figure
        %subplot(1,2,1)
        %plot(X(:,1), X(:,2), '.');
        plot3(X(R,1), X(R,2), X(R,3), '.');
        hold on
        %plot(X(goodLocalRegions{j},1),X(goodLocalRegions{j},2),'rx')
        plot3(X(goodLocalRegions{j},1),X(goodLocalRegions{j},2),X(goodLocalRegions{j},3),'rx')
        x = j;
        plot3(X(opts.seeds(x),1), X(opts.seeds(x),2), X(opts.seeds(x),3), 'k+', 'MarkerSize', 20)
        title(['Est. Dim. = ' num2str(estDims(x))], 'fontSize', 14)
        
        figure;
        %subplot(1,2,1)
        hold on
        sigs = (squeeze(MSVD_Stats(x,:,:)))';
        for dim = 1:D
            plot(Delta(x,:),sigs(:,dim), 'v-')
        end
        plot(repmat(lMinScale(x),1,2), [0, sigs((Delta(x,:)==lMinScale(x)),1)], 'r-')
        plot(repmat(lScale(x),1,2), [0, sigs((Delta(x,:)==lScale(x)),1)], 'g-')
        plot(repmat(lMaxScale(x),1,2), [0, sigs((Delta(x,:)==lMaxScale(x)),1)], 'r-')
        title(['Est. Dim. = ' num2str(estDims(x))], 'fontSize', 14)
        xlabel('Scale', 'fontSize', 14)
        ylabel('Sing.Vals.', 'fontSize', 14)
        hold off
        axis equal
        
%         figure
%         %subplot(1,2,2)
%         hold on
%         for dim = 1:D
%             plot(sigs(:,1),sigs(:,dim), 'v-')
%         end
%         plot(repmat(sigs((Delta(x,:)==lMinScale(x)),1),1,2), [0, sigs((Delta(x,:)==lMinScale(x)),2)], 'r-')
%         plot(repmat(sigs((Delta(x,:)==lScale(x)),1),1,2), [0, sigs((Delta(x,:)==lScale(x)),2)], 'g-')
%         plot(repmat(sigs((Delta(x,:)==lMaxScale(x)),1),1,2), [0, sigs((Delta(x,:)==lMaxScale(x)),2)], 'r-')
%         title(['Est. Dim. = ' num2str(estDims(x))])
%         hold off
%         %axis equal
%         %set(gca, 'ylim', [-0.01 max(sigs(:,1))+0.01])
        
    end
    
end
