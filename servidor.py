from flask import Flask, request, jsonify, send_file
from flask_cors import CORS
import subprocess
import os

app = Flask(__name__)
CORS(app)


import platform
if platform.system() == 'Windows':
    EXECUTAVEL_C = 'conversor.exe'
else:
    EXECUTAVEL_C = './conversor'

@app.route('/')
def index():
    """Serve a página HTML"""
    return send_file('conversor.html')

@app.route('/converter', methods=['POST'])
def converter():
    """
    Recebe dados do HTML e chama o programa C
    """
    try:
        data = request.get_json()
        numero = data.get('numero', '').strip()
        tipo = data.get('tipo', '')
        
        if not numero:
            return jsonify({'erro': 'Número não fornecido'}), 400
        

        if not os.path.exists(EXECUTAVEL_C):
            return jsonify({
                'erro': 'Executável C não encontrado. Compile primeiro: gcc conversor.c -o conversor'
            }), 500
        

        resultado = subprocess.run(
            [EXECUTAVEL_C, tipo, numero],
            capture_output=True,
            text=True,
            timeout=10
        )
        

        saida = resultado.stdout
        

        linhas = saida.split('\n')
        resultado_dict = extrair_resultado(linhas, tipo)
        
        if resultado_dict:
            return jsonify(resultado_dict)
        else:
            return jsonify({'erro': 'Não foi possível processar o resultado'}), 500
            
    except subprocess.TimeoutExpired:
        return jsonify({'erro': 'Timeout: programa C demorou muito'}), 500
    except Exception as e:
        return jsonify({'erro': f'Erro no servidor: {str(e)}'}), 500


def extrair_resultado(linhas, tipo):
    """
    Extrai os valores de Octal, Binário e Decimal da saída do programa C
    """
    resultado = {}
    
    for i, linha in enumerate(linhas):

        if 'Octal:' in linha:

            partes = linha.split(':')
            if len(partes) > 1:
                resultado['octal'] = partes[1].strip()
        
        elif 'Binario:' in linha or 'Binário:' in linha:
            partes = linha.split(':')
            if len(partes) > 1:
                resultado['binario'] = partes[1].strip()
        
        elif 'Decimal:' in linha:
            partes = linha.split(':')
            if len(partes) > 1:
                resultado['decimal'] = partes[1].strip()
        
        elif '[ERRO]' in linha:
            resultado['erro'] = linha.replace('[ERRO]', '').strip()
            return resultado
    
    return resultado


@app.route('/testar', methods=['GET'])
def testar():
    """Endpoint para testar se o servidor está funcionando"""
    return jsonify({
        'status': 'OK',
        'mensagem': 'Servidor funcionando!',
        'executavel_existe': os.path.exists(EXECUTAVEL_C)
    })


if __name__ == '__main__':
    print("="*50)
    print("  SERVIDOR CONVERSOR C + HTML")
    print("="*50)
    print("\n📌 Instruções:")
    print("1. Compile o programa C primeiro:")
    print("   gcc conversor.c -o conversor")
    print("\n2. Acesse no navegador:")
    print("   http://localhost:5000")
    print("\n3. Para parar o servidor: Ctrl+C")
    print("="*50)
    print("\n🚀 Iniciando servidor...\n")
    
    app.run(debug=True, port=5000)