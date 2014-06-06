package com;

import java.io.IOException;
import java.net.InetSocketAddress;
import java.nio.charset.Charset;

import javax.script.ScriptEngine;
import javax.script.ScriptEngineManager;
import javax.script.ScriptException;

import org.apache.mina.core.service.IoAcceptor;
import org.apache.mina.core.service.IoHandlerAdapter;
import org.apache.mina.core.session.IoSession;
import org.apache.mina.filter.codec.ProtocolCodecFilter;
import org.apache.mina.filter.codec.textline.TextLineCodecFactory;
import org.apache.mina.filter.logging.LoggingFilter;
import org.apache.mina.transport.socket.nio.NioSocketAcceptor;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

public class TestCacu {
	private static final int PORT = 10010;

    private static final Logger LOGGER =LoggerFactory.getLogger(TestCacu.class);

    public static void main(String[] args) throws IOException {

        IoAcceptor acceptor =new NioSocketAcceptor(); //建立服務

       acceptor.getFilterChain().addLast("logger", new LoggingFilter());//取得IO服務的過濾器鏈，加入日誌過濾器

       acceptor.getFilterChain().addLast( "codec",new ProtocolCodecFilter(new TextLineCodecFactory(Charset

               .forName("UTF-8")))); //加入字節流和文本流的處理

        acceptor.setHandler(new CalculatorHandler()); //設定處理器

        acceptor.bind(new InetSocketAddress(PORT)); //綁定連接埠

        LOGGER.info("計算器服務已啟動，連接埠是" + PORT);

    }


    
}
class CalculatorHandler extends IoHandlerAdapter { 
    private static final Logger LOGGER = LoggerFactory 
        .getLogger(CalculatorHandler.class); 

    private ScriptEngine jsEngine = null; 

    public CalculatorHandler() { 
        ScriptEngineManager sfm = new ScriptEngineManager(); 
        jsEngine = sfm.getEngineByName("JavaScript"); 
        if (jsEngine == null) { 
            throw new RuntimeException("找不到 JavaScript 引擎。"); 
        } 
    } 

    public void exceptionCaught(IoSession session, Throwable cause) 
        throws Exception { 
        LOGGER.warn(cause.getMessage(), cause); 
    } 

    public void messageReceived(IoSession session, Object message) 
        throws Exception { 
        String expression = message.toString(); 
        if ("quit".equalsIgnoreCase(expression.trim())) { 
            session.close(true); 
            return; 
        } 
        try { 
            Object result = jsEngine.eval(expression); 
            session.write(result.toString()); 
        } catch (ScriptException e) { 
            LOGGER.warn(e.getMessage(), e); 
            session.write("Wrong expression, try again."); 
        } 
    } 
}
   
