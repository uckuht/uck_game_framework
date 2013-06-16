#ifndef TEMP_H_INCLUDED
#define TEMP_H_INCLUDED


mBLOCK("Old code")
    {//1

        bool    col_use = false;
        bool    tex_use = false;
        bool    nor_use = false;

        m_raster.total_size = p_data->fVertexCountGet() * p_data->fVertexSizeOfGet(tex_use, col_use, nor_use);
        m_raster.raster_format = D3DFVF_XYZ;

        if(p_options->diffused && p_data->colors != NULL)
        {//3 color used
            m_raster.raster_format |= D3DFVF_DIFFUSE;
            col_use = true;
        }//3

        if(NULL == m_raster.vertex_buffer)
        {//2
            if(EDONE != sBufferCreate(m_raster.total_size + 1 , m_raster.raster_format, p_data->index_count * 2) )
            {//3
                return EFAIL;
            }//3
        }//2

        float* p_vertex_buffer_temp_data;
        HRESULT RES_OF_LOCK = m_raster.vertex_buffer->Lock( 0, m_raster.total_size, ( void** )&p_vertex_buffer_temp_data, 0 );
        if( FAILED( RES_OF_LOCK ) )
        {//2
            mLOGERROR("vertex lock ");
            return EFAIL;
        }//2

        ui32 pos_step = 3 + ( (col_use)?1:0 ) + ( (tex_use)?2:0 ) + ( (nor_use)?3:0 );
        for(ui32 i = 0; i < p_data->fVertexCountGet(); i ++)
        {//3 copying positions
            ui32 from = i * 3;
            ui32 to = i * pos_step;
            p_vertex_buffer_temp_data[   to   ] = p_data->positions[   from   ];
            p_vertex_buffer_temp_data[ to + 1 ] = p_data->positions[ from + 1 ];
            p_vertex_buffer_temp_data[ to + 2 ] = p_data->positions[ from + 2 ];
        }//3
        if(col_use)
        {//3
            ui32 col_ofs = 3;
            for(ui32 i = 0; i < p_data->fVertexCountGet(); i++)
            {//3 colors
                ui32 to = i * pos_step + col_ofs;
                (si32&)p_vertex_buffer_temp_data[ to ] = p_data->colors[i];
            }//3
        }//3
        m_raster.vertex_buffer->Unlock();

        if(NULL != p_data->indexes)
        {//3
             ui16*  index_data;
             m_raster.index_buffer->Lock(0,p_data->index_count*sizeof(ui16),(void**)&index_data,D3DLOCK_DISCARD);
             memcpy(index_data,p_data->indexes,p_data->index_count*sizeof(ui16));
             m_raster.index_buffer->Unlock();
        }//3
        if(NULL == m_raster.index_buffer)
        {//3
            m_raster.primitive_count = p_data->vertex_count / 3;
        }//3
        else
        {//3 index onn
            m_raster.primitive_count = p_data->index_count / 3;
        }//3
        m_raster.vertex_size = p_data->fVertexSizeOfGet(tex_use,col_use,nor_use);
        m_raster.vertex_count = p_data->vertex_count;

        sDrawRasterData();
    }//1
    return EDONE;

#endif // TEMP_H_INCLUDED
