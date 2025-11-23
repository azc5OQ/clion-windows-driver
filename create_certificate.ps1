# generate_cert.ps1 (created by chatgpt)
# even if windows has active test signing and disabled DSE, driver still needs to be signed with test cert

$certName = "CN=MyTestCert"
$certPath = "Cert:\CurrentUser\My"  # Use CurrentUser store (no admin required)

# Get the directory where the script is located (current working directory)
$pfxPath = Join-Path -Path $PSScriptRoot -ChildPath "MyTestCert.pfx"

$password = "password123"

# Check if the certificate already exists in the CurrentUser store
$existingCert = Get-ChildItem -Path $certPath | Where-Object {$_.Subject -eq $certName}

if ($existingCert -eq $null) {
    Write-Host "Certificate not found. Creating new certificate..."

    # Create the self-signed certificate in the CurrentUser store
    $cert = New-SelfSignedCertificate -Type CodeSigningCert -Subject $certName -CertStoreLocation $certPath

    Write-Host "Certificate created."
} else {
    Write-Host "Certificate already exists."
}

# Now, check if the .pfx file already exists
if (-Not (Test-Path -Path $pfxPath)) {
    Write-Host "Exporting certificate to .pfx file..."

    # Export the certificate to a .pfx file
    $pwd = ConvertTo-SecureString -String $password -Force -AsPlainText
    Export-PfxCertificate -Cert $existingCert -FilePath $pfxPath -Password $pwd

    Write-Host "Certificate exported to $pfxPath."
} else {
    Write-Host "PFX file already exists. Skipping export."
}
