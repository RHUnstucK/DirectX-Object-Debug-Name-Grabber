std::string GetDebugName(ID3D11DeviceChild* pObject)
{
    if (!pObject)
        return {};

    UINT dataSize = 0;

    HRESULT hResult = pObject->GetPrivateData(WKPDID_D3DDebugObjectName, &dataSize, nullptr);
    if (FAILED(hResult) || dataSize == 0)
        return {};

    std::vector<char> name(dataSize + 1);  // +1 for potential null-terminator
    UINT size = dataSize;

    hResult = pObject->GetPrivateData(WKPDID_D3DDebugObjectName, &size, name.data());
    if (SUCCEEDED(hResult))
        return std::string(name.data());

    return {};
}

ID3D11PixelShader* pPixelShader = nullptr;
pContext->PSGetShader(&pPixelShader, nullptr, nullptr);

std::string debugName = GetDebugName(pPixelShader);

if (pPixelShader)
{
    pPixelShader->Release();

    // Get the shader resources bound to the pixel shader
    ID3D11ShaderResourceView* pSRV = nullptr;
    pContext->PSGetShaderResources(0, 1, &pSRV);

    if (pSRV)
    {
        ID3D11Resource* pResource = nullptr;
        pSRV->GetResource(&pResource);

        if (pResource)
        {
            std::string debugName = GetDebugName(pResource);
            pResource->Release();
        }

        pSRV->Release();
    }
}